/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:51:57 by jole              #+#    #+#             */
/*   Updated: 2023/04/26 16:56:13 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_exit_code(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	builtin_exit(char **args)
{
	ft_putstr_fd("exit\n", 2);
	if (!args)
		exit(g_vars.last_exit);
	if (check_exit_code(args[0]) == -1)
		exit(-1);
	if (args[1])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (-1);
	}
	exit(ft_atoi(args[0]));
}
