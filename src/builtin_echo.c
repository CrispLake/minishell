/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:40:44 by jole              #+#    #+#             */
/*   Updated: 2023/04/18 18:30:00 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_echo(char **array)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "-n", 3) == 0)
		{
			i++;
			flag = 1;
		}
		else
			break ;
	}
	while (array[i])
	{
		printf("%s", array[i++]);
		if (array[i] != NULL)
			printf(" ");
	}
	if (flag != 1)
		printf("\n");
}
