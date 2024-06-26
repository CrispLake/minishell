/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:35:02 by emajuri           #+#    #+#             */
/*   Updated: 2024/06/04 19:56:50 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child(char **cmd, t_fd *fds)
{
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

int	redirect_or_skip(t_fd *fds, t_command *cmd, int total)
{
	if (make_fd(fds, total, fds->pipe[0], cmd->redi))
	{
		parent(fds);
		return (-1);
	}
	if (!cmd->cmd[0] && !g_vars.status)
	{
		parent(fds);
		return (-1);
	}
	return (0);
}

int	parent_and_child(t_fd *fds, t_command *cmds, int i, int *pids)
{
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
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		child(cmds[i].cmd, fds);
	}
	parent(fds);
	return (0);
}

int	loop_cmds(t_command *cmds, t_fd *fds, int total, int *pids)
{
	int	i;

	i = 0;
	while (total--)
	{
		signal(SIGINT, SIG_IGN);
		if (redirect_or_skip(fds, &cmds[i++], total))
			continue ;
		if (g_vars.status)
		{
			g_vars.status = 0;
			parent(fds);
			free(pids);
			if (fds->pipe[0] > 2)
				close(fds->pipe[0]);
			return (-1);
		}
		if (parent_and_child(fds, cmds, i - 1, pids))
			return (-1);
	}
	return (0);
}

int	execute_cmds(t_command *cmds)
{
	t_fd	fds;
	int		total;
	int		*pids;

	total = count_cmds(cmds);
	ft_bzero(&fds, sizeof(t_fd));
	if (total == 1 && check_for_builtin(cmds->cmd[0]))
		return (builtin_with_redi(cmds, &fds, 0, 0));
	pids = ft_calloc(total, sizeof(int));
	if (!pids)
	{
		free_commands(cmds);
		return (-1);
	}
	if (loop_cmds(cmds, &fds, total, pids))
	{
		free_commands(cmds);
		return (-1);
	}
	wait_all(pids, total);
	free(pids);
	free_commands(cmds);
	return (0);
}
