/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 17:46:30 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/20 16:54:04 by emajuri          ###   ########.fr       */
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

enum e_builtins
{
	B_ECHO = 1,
	B_CD = 2,
	B_PWD = 3,
	B_EXPORT = 4,
	B_UNSET = 5,
	B_ENV = 6,
	B_EXIT = 7
};

int	make_fd(t_fd *fds, int total, int old, char **redi);
int	execute_cmds(t_command *cmds);

#endif
