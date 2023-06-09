/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:56:30 by jole              #+#    #+#             */
/*   Updated: 2023/04/26 21:35:01 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_vector(t_vector *v_str)
{
	char	*tmp;
	int		i;

	tmp = v_str->str;
	v_str->str = ft_calloc((v_str->size + 50), sizeof(char));
	if (!v_str->str)
	{
		free(tmp);
		return (-1);
	}
	v_str->size += 50;
	i = -1;
	while (tmp[++i])
		v_str->str[i] = tmp[i];
	v_str->str[i] = '\0';
	free(tmp);
	return (0);
}

int	expand_dollar(t_vector *v_str)
{
	char	*tmp;
	int		i;

	tmp = ft_itoa(g_vars.last_exit);
	if (!tmp)
		return (-1);
	i = -1;
	while (tmp[++i])
	{
		if (v_str->chars + 2 > v_str->size)
			if (expand_vector(v_str) == -1)
				return (-1);
		v_str->str[v_str->chars++] = tmp[i];
	}
	return (-2);
}

int	if_env_expand(t_vector *v_str, char *str, int len, int i)
{
	int	x;

	x = len + 1;
	if (str[0] == '?')
		return (expand_dollar(v_str));
	while (g_vars.env.env[i])
	{
		if (!ft_strncmp(g_vars.env.env[i], str, len) && \
				g_vars.env.env[i][len] == '=')
		{
			while (g_vars.env.env[i][x])
				if (copy_char(v_str, g_vars.env.env[i], &x))
					return (-1);
			return (len);
		}
		i++;
	}
	return (len);
}

int	init_vector(t_vector *v_str)
{
	v_str->size = 50;
	v_str->str = ft_calloc(v_str->size, sizeof(char));
	if (!v_str->str)
		return (-1);
	v_str->chars = 0;
	return (0);
}

int	copy_char(t_vector *v_str, char *str, int *i)
{
	if (v_str->chars + 2 > v_str->size)
	{
		if (expand_vector(v_str))
			return (-1);
	}
	v_str->str[v_str->chars++] = str[*i];
	(*i)++;
	return (0);
}
