/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:06:11 by jole              #+#    #+#             */
/*   Updated: 2023/04/20 14:52:52 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_env(void)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 0;
	ft_bzero(&g_vars, sizeof(t_vars));
	while (environ[i])
		i++;
	g_vars.env.size = i + 5;
	g_vars.env.env = ft_calloc((i + 5), sizeof(char *));
	if (!g_vars.env.env)
		return (-1);
	j = 0;
	while (environ[j])
	{
		i = ft_strlen(environ[j]);
		g_vars.env.env[j] = ft_calloc((i + 1), sizeof(char));
		if (!g_vars.env.env[j])
			return (-1);
		ft_strlcpy(g_vars.env.env[j], environ[j], i + 1);
		g_vars.env.items++;
		i = 0;
		j++;
	}
	return (0);
}
