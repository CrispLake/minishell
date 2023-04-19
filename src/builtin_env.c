/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:02:36 by jole              #+#    #+#             */
/*   Updated: 2023/04/19 18:40:00 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_env(void)
{
	int	i;

	i = 0;
	while (g_vars.env.env[i])
	{
		if (ft_strchr(g_vars.env.env[i], '=') != 0)
			printf("%s\n", g_vars.env.env[i]);
		i++;
	}
	return (0);
}
