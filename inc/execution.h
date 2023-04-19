/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:46:30 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/19 14:54:16 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
}	t_fd;

typedef struct s_command
{
	char	**cmd;
	char	**redi;
}	t_command;

enum builtins
{
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7
};

int	make_fd(t_fd *fds, int total, int *old, char **redi);

#endif
