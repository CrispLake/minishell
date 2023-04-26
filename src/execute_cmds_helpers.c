/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:38:03 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/26 15:01:46 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/wait.h>

void	wait_all(int *pids, int total)
{
	int	i;
	int	status;
	int	check;
	int	signal;

	i = 0;
	check = 0;
	while (i < total)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			g_vars.last_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && check++ == 0)
		{
			signal = WTERMSIG(status);
			if (signal == 3)
				printf("Quit: %d", signal);
			printf("\n");
			g_vars.last_exit = signal + 128;
		}
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

void	parent(t_fd *fds)
{
	if (fds->fd_in)
		close(fds->fd_in);
	if (fds->fd_out)
		close(fds->fd_out);
	fds->fd_in = 0;
	fds->fd_out = 0;
}

void	sigint_heredoc(int sig)
{
	char	buf[2];

	(void)sig;
	g_vars.status = 1;
	buf[0] = 4;
	buf[1] = 0;
	ioctl(STDIN_FILENO, TIOCSTI, buf);
}
