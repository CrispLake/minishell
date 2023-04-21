/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:35:02 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/21 13:54:33 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int	count_cmds(t_command *cmds)
{
	int	i;
	
	i = 0;
	while (cmds[i].cmd)
		i++;
	return (i);
}

int	check_for_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5))
		return (B_ECHO);
	if (!ft_strncmp(cmd, "cd", 3))
		return (B_CD);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (B_PWD);
	if (!ft_strncmp(cmd, "export", 7))
		return (B_EXPORT);
	if (!ft_strncmp(cmd, "unset", 6))
		return (B_UNSET);
	if (!ft_strncmp(cmd, "env", 4))
		return (B_ENV);
	if (!ft_strncmp(cmd, "exit", 5))
		return (B_EXIT);
	return (0);
}

int	call_builtin(char **cmd)
{
	int	ret;
	int	builtin;

	ret = 0;
	builtin = check_for_builtin(cmd[0]);
	printf("BUILTIN: %d\n", builtin);
	if (builtin == ECHO)
		ret = 0;
	else if (builtin == B_CD)
		ret = 0;
	else if (builtin == B_PWD)
		ret = builtin_pwd();
	else if (builtin == B_EXPORT)
		ret = builtin_export(cmd[1]);
	else if (builtin == B_UNSET)
		ret = builtin_unset(cmd[1]);
	else if (builtin == B_ENV)
		ret = builtin_env();
	else if (builtin == B_EXIT)
		ret = 0;
	return (ret);
}

int	test_paths(char **cmd)
{
	char	**paths;
	int		i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	while (g_vars.env.env[i] && ft_strncmp(g_vars.env.env[i], "PATH=", 5))
		i++;
	if (!g_vars.env.env[i])
		return (-1);
	paths = ft_split(&g_vars.env.env[i][5], ':');
	if (!paths)
		return (-1);
	i = 0;
	while (paths[i])
	{
		tmp1 = ft_strjoin(paths[i], "/");
		if (!tmp1)
		{
			free_double_pointer(paths);
			return (-1);
		}
		tmp2 = ft_strjoin(tmp1, cmd[0]);
		free(tmp1);
		if (!tmp2)
		{
			free_double_pointer(paths);
			return (-1);
		}
		if (!access(tmp2, F_OK | R_OK | X_OK))
		{
			free_double_pointer(paths);
			free(cmd[0]);
			cmd[0] = tmp2;
			return (0);
		}
		free(tmp2);
		i++;
	}
	free_double_pointer(paths);
	return (-1);
}

int	add_filepath(char **cmd)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) || access(cmd[0], R_OK | X_OK))
		{
			perror("minishell: COMMAND HERE SOMEHOW");
			return (-1);
		}
	}
	else if (!check_for_builtin(cmd[0]) && test_paths(cmd))
		{
			perror("minishell: COMMAND HERE SOMEHOW");
			return (-1);
		}
	return (0);
}

void	child(char **cmd, t_fd *fds)
{
	//builtin_export(""); shllvl+1;
	if (fds->fd_in)
	{
		if (dup2(fds->fd_in, STDIN_FILENO))
		{
			perror("minishell");
			exit(-1);
		}
		close(fds->fd_in);
	}
	if (fds->fd_out)
	{
		if (dup2(fds->fd_out, STDOUT_FILENO))
		{
			perror("minishell");
			exit(-1);
		}
		close(fds->fd_out);
	}
	if (fds->pipe[0])
		close(fds->pipe[0]);
	execve(cmd[0], cmd, g_vars.env.env);
	perror("minishell");
	exit(-1);
}

void	parent(t_fd *fds)
{
	if (fds->fd_in)
		close(fds->fd_in);
	if (fds->fd_out)
		close(fds->fd_out);
	fds->fd_in = 0;
	fds->fd_out = 0;
}

void	wait_all(int *pids, int total)
{
	int	i;
	int	status;

	i = 0;
	while(i < total)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
}

int	execute_cmds(t_command *cmds)
{
	t_fd	fds;
	int		i;
	int		total;
	int		savetotal;
	int		*pids;

	i = 0;
	total = count_cmds(cmds);
	savetotal = total;
	printf("Total command count: %d\n", total);
	if (total == 1 && check_for_builtin(cmds->cmd[0]))
		return (call_builtin(cmds->cmd));
	pids = ft_calloc(total, sizeof(int));
	if (!pids)
		return (-1);
	ft_bzero(&fds, sizeof(t_fd));
	while (total--)
	{
		if (make_fd(&fds, total, fds.pipe[0], cmds[i].redi))
			continue ;
		if (!cmds[i].cmd[0])
		{
			parent(&fds);
			continue ;
		}
		if (add_filepath(cmds[i].cmd))
		{
			free(pids);
			return (-1);
		}
		pids[i] = fork();
		if (pids[i] == -1)
		{
			free(pids);
			return (-1);
		}
		else if (pids[i] == 0)
			child(cmds[i].cmd, &fds);
		parent(&fds);
		i++;
	}
	wait_all(pids, savetotal);
	free(pids);
	return (0);
}
