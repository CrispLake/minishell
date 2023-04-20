/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:47:46 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/20 17:40:49 by emajuri          ###   ########.fr       */
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

int	make_fd(t_fd *fds, int total, int old, char **redi)
{
	int	i;
	// int	file;

	i = 0;
	if (total && pipe(fds->pipe))
	{
		if (old)
			close(old);
		return (-1);
	}
	if (old)
		fds->fd_in = old;
	if (total)
		fds->fd_out = fds->pipe[1];
	while (redi[i])
	{
	}
	return (0);
}
