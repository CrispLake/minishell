/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:02:58 by jole              #+#    #+#             */
/*   Updated: 2023/04/18 12:26:19 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_env(void)
{
	int		i;
	int		len;
	char	**tmp;

	tmp = g_vars.env.env;
	g_vars.env.env = ft_calloc((g_vars.env.size + 5), sizeof(char *));
	if (!g_vars.env.env)
		return (-1);
	g_vars.env.size += 5;
	i = -1;
	while (tmp[++i])
	{
		len = ft_strlen(tmp[i]);
		g_vars.env.env[i] = ft_calloc((len + 1), sizeof(char));
		if (!g_vars.env.env[i])
		{
			free_double_pointer(tmp);
			free_double_pointer(g_vars.env.env);
			return (-1);
		}
		ft_strlcpy(g_vars.env.env[i], tmp[i], len + 1);
	}
	i = 0;
	free_double_pointer(tmp);
	return (0);
}

int	check_for_env_duplicates(char *str)
{
	int		i;
	int		len;
	char	*new_str;
	char	*check;

	i = -1;
	check = ft_strchr(str, '=');
	if (!check)
		return (-1);
	len = check - str + 1;
	if (len - 1 < 1)
		return (-1);
	while (g_vars.env.env[++i])
	{
		if (ft_strncmp(g_vars.env.env[i], str, len) == 0)
		{
			new_str = ft_strdup(str);
			if (!new_str)
				return (-1);
			g_vars.env.env[i] = new_str;
			return (1);
		}
	}
	return (0);
}

int	check_env_name(char *str)
{
	int		i;
	int		len;
	char	*check;

	check = ft_strchr(str, '=');
	if (!check)
		return (-1);
	len = check - str;
	i = 1;
	if (!ft_isalpha(*str) && len)
		return (-1);
	while (str[i] && (len - 1))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
		len--;
	}
	return (0);
}

int	builtin_export(char *str)
{
	int	i;

	if (g_vars.env.items + 1 >= g_vars.env.size)
		if (expand_env() == -1)
			return (-1);
	if (check_env_name(str) == -1)
		return (-1);
	i = check_for_env_duplicates(str);
	if (i == -1 || i == 1)
	{
		if (i == -1)
			return (-1);
		return (0);
	}
	i = 0;
	g_vars.env.env[g_vars.env.items] = ft_calloc((ft_strlen(str) + 1), \
			sizeof(char));
	i = 0;
	while (str[i])
	{
		g_vars.env.env[g_vars.env.items][i] = str[i];
		i++;
	}
	g_vars.env.items++;
	return (0);
}
