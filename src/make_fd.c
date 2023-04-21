/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:47:46 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/21 13:37:08 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	input_redi(t_fd *fds, char **redi)
{
	close(fds->fd_in);
	if (redi[0][1] == '<')
		return (-1);
	fds->fd_in = open(redi[1], O_RDONLY);
	if (fds->fd_in < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	output_redi(t_fd *fds, char **redi)
{
	close(fds->fd_out);
	if (redi[0][1] == '>')
		fds->fd_out = open(redi[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fds->fd_out = open(redi[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fds->fd_out < 0)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	redirections(t_fd *fds, char **redi)
{
	int	i;

	i = 0;
	while (redi[i])
	{
		if (redi[i][0] == '<')
		{
			if (input_redi(fds, &redi[i]))
				return (-1);
		}
		else
			if (output_redi(fds, &redi[i]))
				return (-1);
		i += 2;
	}
	return (0);
}

int	make_fd(t_fd *fds, int total, int old, char **redi)
{
	if (total && pipe(fds->pipe))
	{
		if (old)
			close(old);
		return (-1);
	}
	if (old)
		fds->fd_in = old;
	else
		fds->fd_in = 0;
	if (total)
	{
		fds->fd_out = fds->pipe[1];
		fds->pipe[1] = 0;
	}
	else
		fds->fd_out = 0;
	if (redi)
		if (redirections(fds, redi))
			return (-1);
	return (0);
}
