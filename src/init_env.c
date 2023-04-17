/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 20:54:40 by jole              #+#    #+#             */
/*   Updated: 2023/04/17 13:14:14 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_env(void)
{
	extern char	**environ;
	int	i;
	int	j;

	i = 0;
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
