/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:58:02 by emajuri           #+#    #+#             */
/*   Updated: 2023/05/05 14:14:18 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	g_vars.last_exit = ret;
	return (ret);
}

static int	dup2_error(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	builtin_with_redi(t_command *cmd, t_fd *fds, int ret, int save_stdout)
{
	if (make_fd(fds, 0, 0, cmd->redi))
	{
		free_commands(cmd);
		return (-1);
	}
	if (fds->fd_out)
	{
		save_stdout = dup(STDOUT_FILENO);
		if (dup2_error(fds->fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	ret = call_builtin(cmd->cmd);
	if (fds->fd_out)
	{
		close(fds->fd_out);
		if (dup2_error(save_stdout, STDOUT_FILENO) == -1)
			return (-1);
		close(save_stdout);
	}
	free_commands(cmd);
	return (ret);
}
