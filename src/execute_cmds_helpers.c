/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:38:03 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/24 16:45:05 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_all(int *pids, int total)
{
	int	i;
	int	status;

	i = 0;
	while (i < total)
	{
		waitpid(pids[i], &status, 0);
		g_vars.last_exit = status;
		i++;
	}
}

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
