/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 12:02:58 by jole              #+#    #+#             */
/*   Updated: 2023/05/02 18:51:27 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_env(void)
{
	int		i;
	char	**tmp;

	tmp = g_vars.env.env;
	g_vars.env.env = ft_calloc((g_vars.env.size + 5), sizeof(char *));
	if (!g_vars.env.env)
	{
		free_double_pointer(tmp);
		return (-1);
	}
	g_vars.env.size += 5;
	i = -1;
	while (tmp[++i])
	{
		g_vars.env.env[i] = ft_calloc((ft_strlen(tmp[i]) + 1), sizeof(char));
		if (!g_vars.env.env[i])
		{
			free_double_pointer(tmp);
			free_double_pointer(g_vars.env.env);
			return (-1);
		}
		ft_strlcpy(g_vars.env.env[i], tmp[i], ft_strlen(tmp[i]) + 1);
	}
	free_double_pointer(tmp);
	return (0);
}

int	check_env_name(char *str)
{
	int		i;
	int		len;
	char	*check;

	check = ft_strchr(str, '=');
	if (check != 0)
		len = check - str;
	else
		len = ft_strlen(str);
	i = 1;
	if (!ft_isalpha(*str) && str[0] != '_' && len)
	{
		printf("minishell: export: '%s': not a valid identifier\n", str);
		return (-1);
	}
	while (str[i] && (len - 1))
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (-1);
		i++;
		len--;
	}
	return (0);
}

int	export_string(char *str)
{
	int	i;

	if (g_vars.env.items + 1 >= g_vars.env.size)
		if (expand_env() == -1)
			return (-1);
	if (check_env_name(str) == -1)
		return (-1);
	i = check_for_env_duplicates(str, ft_strchr(str, '='), -1, 0);
	if (i == -1)
		return (-1);
	if (i == 1)
		return (0);
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

int	builtin_export(char **args)
{
	int	i;
	int	c;

	i = 0;
	if (!args[0])
	{
		while (g_vars.env.env[i])
		{
			c = 0;
			printf("declare -x ");
			while (g_vars.env.env[i][c] != '=' && g_vars.env.env[i][c])
				printf("%c", g_vars.env.env[i][c++]);
			if (g_vars.env.env[i][c])
				printf("%c\"%s\"", g_vars.env.env[i][c], \
						&g_vars.env.env[i][c + 1]);
			printf("\n");
			i++;
		}
		return (0);
	}
	while (args[i])
		export_string(args[i++]);
	return (0);
}
