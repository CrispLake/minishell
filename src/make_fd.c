/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:47:46 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/19 15:18:22 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>


// void	dup_fds(t_vars *vars, int fd1, int fd2)
// {
// 	vars->fd_in = dup(fd1);
// 	if (vars->fd_in == -1)
// 		free_perror(vars->pids);
// 	if (close(fd1) == -1)
// 		free_perror(vars->pids);
// 	vars->fd_out = dup(fd2);
// 	if (vars->fd_out == -1)
// 		free_perror(vars->pids);
// 	if (close(fd2) == -1)
// 		free_perror(vars->pids);
// }

int	make_fd(t_fd *fds, int total, int *old_pipe, char **redi)
{
	int	old[2];

	old[0] = old_pipe[0];
	old[1] = old_pipe[1];
	if (pipe(fds->pipe))
		exit(-1);
	return (0);
}
