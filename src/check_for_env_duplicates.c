/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_env_duplicates.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:50:26 by emajuri           #+#    #+#             */
/*   Updated: 2023/05/02 18:53:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	decide(char	*str, int len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i > len)
		return (i);
	return (len);
}

int	len_of_variable(char *str, char *check)
{
	int	len;

	len = 0;
	if (check != 0)
	{
		len = check - str;
		if (len - 1 < 1)
			return (-1);
	}
	else
		len = ft_strlen(str);
	return (len);
}

int	check_for_env_duplicates(char *str, char *check, int i, int len)
{
	char	*new_str;

	len = len_of_variable(str, check);
	if (len == -1)
		return (-1);
	while (g_vars.env.env[++i])
	{
		if (ft_strncmp(g_vars.env.env[i], str,
				decide(g_vars.env.env[i], len)) == 0)
		{
			if (str[len] == '=')
			{
				new_str = ft_strdup(str);
				if (!new_str)
					return (-1);
				free(g_vars.env.env[i]);
				g_vars.env.env[i] = new_str;
			}
			return (1);
		}
	}
	return (0);
}
