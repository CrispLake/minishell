/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:35:02 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/24 13:49:53 by emajuri          ###   ########.fr       */
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
	if (builtin == B_ECHO)
		ret = builtin_echo(&cmd[1]);
	else if (builtin == B_CD)
		ret = builtin_cd(&cmd[1]);
	else if (builtin == B_PWD)
		ret = builtin_pwd();
	else if (builtin == B_EXPORT)
		ret = builtin_export(&cmd[1]);
	else if (builtin == B_UNSET)
		ret = builtin_unset(&cmd[1]);
	else if (builtin == B_ENV)
		ret = builtin_env();
	else if (builtin == B_EXIT)
		ret = builtin_exit(&cmd[1]);
	return (ret);
}

int	builtin_with_redi(t_command *cmd, t_fd *fds)
{
	int	ret;
	int	save_stdout;

	ret = 0;
	make_fd(fds, 0, 0, cmd->redi);
	if (fds->fd_out)
	{
		save_stdout = dup(STDOUT_FILENO);
		if (dup2(fds->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (-1);
		}
	}
	ret = call_builtin(cmd->cmd);
	if (fds->fd_out)
	{
		if (dup2(save_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			return (-1);
		}
	}
	return (ret);
}

void	child(char **cmd, t_fd *fds)
{
	increment_shlvl();
	if (fds->fd_in)
	{
		if (dup2(fds->fd_in, STDIN_FILENO) == -1)
		{
			perror("minishell");
			exit(-1);
		}
		close(fds->fd_in);
	}
	if (fds->fd_out)
	{
		if (dup2(fds->fd_out, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			exit(-1);
		}
		close(fds->fd_out);
	}
	if (fds->pipe[0])
		close(fds->pipe[0]);
	if (check_for_builtin(cmd[0]))
		exit(call_builtin(cmd));
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
		g_vars.last_exit = status;
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
	ft_bzero(&fds, sizeof(t_fd));
	if (total == 1 && check_for_builtin(cmds->cmd[0]))
		return (builtin_with_redi(cmds, &fds));
	pids = ft_calloc(total, sizeof(int));
	if (!pids)
		return (-1);
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
