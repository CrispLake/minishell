/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:05:50 by jole              #+#    #+#             */
/*   Updated: 2023/04/26 22:04:47 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	copy_till_quotes(t_vector *v_str, char *str, int len, int i)
{
	int	check;

	while (str[i] && str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == '$' && (str[i + 1] == '_' || ft_isalpha(str[i + 1]) || \
			str[i + 1] == '?'))
		{
			i++;
			len = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				len++;
				i++;
			}
			check = if_env_expand(v_str, &str[i - len], len, 0);
			if (check == -2)
				i++;
			else if (check == -1)
				return (-1);
		}
		else
			if (copy_char(v_str, str, &i))
				return (-1);
	}
	return (i);
}

int	copy_till_delim_single(t_vector *v_str, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		if (copy_char(v_str, str, &i))
			return (-1);
	return (i + 1);
}

int	copy_till_delim_double(t_vector *v_str, char *str, int i, int len)
{
	int	check;

	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && (str[i + 1] == '_' || \
			ft_isalpha(str[i + 1]) || str[i + 1] == '?') && ++i > 0)
		{
			len = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				len++;
				i++;
			}
			check = if_env_expand(v_str, &str[i - len], len, 0);
			if (check == -2)
				i++;
			else if (check == -1)
				return (-1);
		}
		else
			if (copy_char(v_str, str, &i))
				return (-1);
	}
	return (i + (str[i] == '\"'));
}

char	*expand_var_in_string(char *str, int i, int delim, int error_check)
{
	t_vector	v_str;

	if (init_vector(&v_str))
		return (str);
	while (str[i])
	{
		delim = 0;
		error_check = i;
		if ((str[i] == '\'' || str[i] == '\"') && ++error_check > 0)
			delim = str[i++];
		else
			i += copy_till_quotes(&v_str, &str[i], 0, 0);
		if (str[i] && delim == '\'')
			i += copy_till_delim_single(&v_str, &str[i]);
		else if (str[i] && delim == '\"')
			i += copy_till_delim_double(&v_str, &str[i], 0, 0);
		if (error_check > i)
		{
			free(v_str.str);
			return (NULL);
		}
	}
	return (v_str.str);
}

int	expand_variables(t_token *tokens)
{
	int		i;
	char	*tmp;
	char	*new_str;

	i = 0;
	while (tokens[i].type != -1)
	{
		tmp = expand_var_in_string(tokens[i].str, 0, 0, 0);
		if (!tmp)
			return (-1);
		new_str = ft_strdup(tmp);
		free(tmp);
		if (!new_str)
			return (-1);
		free(tokens[i].str);
		tokens[i++].str = new_str;
	}
	return (0);
}
