/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:35:02 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/18 20:14:00 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_cmds(t_command *cmds)
{
	int	i;
	
	i = 0;
	while (cmds[i].cmd)
		i++;
	return (i);
}

int	check_for_builtin(char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5))
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3))
		return (1);
	if (ft_strncmp(cmd[0], "pwd", 4))
		return (1);
	if (ft_strncmp(cmd[0], "export", 7))
		return (1);
	if (ft_strncmp(cmd[0], "unset", 6))
		return (1);
	if (ft_strncmp(cmd[0], "cd", 3))
		return (1);
	return (0);
}

int	execute_cmds(t_command *cmds)
{
	t_fd	fds;
	int		i;
	int		count;

	i = 0;
	count = count_cmds(cmds);
	if (count == 1)
	while (cmds[i].cmd)
	{
		make_fd(argc - 3, &vars, vars.new, argv);
		cmd = add_filepath(argv, vars.count + 1);
		if (!cmd)
			filepath_error(vars.pids);
		vars.pids[vars.count - 1] = fork();
		if (vars.pids[vars.count - 1] == -1)
			fork_error(cmd, &vars, argc - 3);
		else if (vars.pids[vars.count - 1] == 0)
			child(&vars, vars.new, cmd, argc - 3);
		parent(&vars, cmd);
	}
	wait_all(vars.pids, vars.count - 2);
	return (0);
}

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
//
// void	first_command(t_vars *vars, char *file, int old0, int old1)
// {
// 	int	file1;
//
// 	file1 = open(file, O_RDONLY);
// 	if (file1 == -1)
// 	{
// 		perror("Opening file 1 failed");
// 		close(vars->new[0]);
// 		close(vars->new[1]);
// 		exit(-1);
// 	}
// 	dup_fds(vars, file1, old1);
// 	vars->new[0] = old0;
// }
//
// void	make_fd(int commands, t_vars *vars, int *old, char **argv)
// {
// 	int	file2;
// 	int	old0;
// 	int	old1;
//
// 	old0 = old[0];
// 	old1 = old[1];
// 	if (vars->count != 1 && vars->count != commands)
// 		if (pipe(vars->new))
// 			exit(-1);
// 	if (vars->count == 1)
// 		first_command(vars, argv[vars->count], old0, old1);
// 	else if (vars->count < commands)
// 		dup_fds(vars, old0, vars->new[1]);
// 	else
// 	{
// 		file2 = open(argv[commands + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (file2 == -1)
// 		{
// 			perror("Opening file 2 failed");
// 			close(old[0]);
// 			exit(-1);
// 		}
// 		dup_fds(vars, old0, file2);
// 	}
// }
