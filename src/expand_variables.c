/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:05:50 by jole              #+#    #+#             */
/*   Updated: 2023/04/26 19:55:13 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	copy_till_quotes(t_vector *v_str, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			i++;
			len = 0;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				len++;
				i++;
			}
			if (if_env_expand(v_str, &str[i - len], len, 0) == -2)
				i++;
		}
		else
		{
			if (v_str->chars + 2 > v_str->size)
				expand_vector(v_str);
			v_str->str[v_str->chars++] = str[i++];
		}
	}
	return (i);
}

int	copy_till_delim_single(t_vector *v_str, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
	{
		if (v_str->chars + 2 > v_str->size)
			expand_vector(v_str);
		v_str->str[v_str->chars++] = str[i++];
	}
	return (i + 1);
}

int	copy_till_delim_double(t_vector *v_str, char *str, int i, int len)
{
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || \
				str[i] == '$') && str[i] != '\"')
	{
		if (str[i] == '$' && ++i > 0)
		{
			len = 0;
			while (str[i] && (ft_isalnum(str[i]) || \
						str[i] == '_' || str[i] == '\''))
			{
				len++;
				i++;
			}
			if (if_env_expand(v_str, &str[i - len], len, 0) == -2)
				i++;
		}
		else
		{
			if (v_str->chars + 2 > v_str->size)
				expand_vector(v_str);
			v_str->str[v_str->chars++] = str[i++];
		}
	}
	if (str[i] && str[i] != '\"')
		return (i);
	return (i + 1);
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
			i += copy_till_quotes(&v_str, &str[i], 0);
		if (str[i] && delim == '\'')
			i += copy_till_delim_single(&v_str, &str[i]);
		else if (str[i] && delim == '\"')
			i += copy_till_delim_double(&v_str, &str[i], 0, 0);
		if (error_check > i)
			return (error_in_check(&v_str));
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
