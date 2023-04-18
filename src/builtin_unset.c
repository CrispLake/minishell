/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:05:24 by jole              #+#    #+#             */
/*   Updated: 2023/04/18 12:29:58 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_env(char *str, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	while (g_vars.env.env[i])
	{
		if (ft_strncmp(g_vars.env.env[i], str, len) == 0)
		{
			tmp = g_vars.env.env[i];
			g_vars.env.env[i] = g_vars.env.env[i + 1];
			free(tmp);
			while (g_vars.env.env[++i])
				g_vars.env.env[i] = g_vars.env.env[i + 1];
			g_vars.env.env[i] = NULL;
			break ;
		}
		i++;
	}
}

int	builtin_unset(char *str)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(str);
	if (ft_strchr(str, '=') != NULL)
		return (0);
	while (g_vars.env.env[++i])
	{
		if (ft_strncmp(g_vars.env.env[i], str, len) == 0)
		{
			delete_env(str, len);
			g_vars.env.items--;
			break ;
		}
	}
	return (0);
}
