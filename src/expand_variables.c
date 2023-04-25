/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:05:50 by jole              #+#    #+#             */
/*   Updated: 2023/04/25 18:58:28 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	copy_till_quotes(t_vector *v_str, char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			i++;
			len = 0;
			while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ' ')
			{
				len++;
				i++;
			}
			if_env_expand(v_str, &str[i - len], len);
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

int	copy_till_delim_double(t_vector *v_str, char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$')
		{
			i++;
			len = 0;
			while (str[i] && str[i] != '\"' && str[i] != '\'' && str[i] != ' ')
			{
				len++;
				i++;
			}
			if_env_expand(v_str, &str[i - len], len);
		}
		else
		{
			if (v_str->chars + 2 > v_str->size)
				expand_vector(v_str);
			v_str->str[v_str->chars++] = str[i++];
		}
	}
	return (i + 1);
}

char	*expand_var_in_string(char *str)
{
	t_vector	v_str;
	char		*new_str;
	int			i;
	int			delim;
	//int			error_check;

	v_str.size = 50;
	v_str.str = ft_calloc(v_str.size, sizeof(char));
	v_str.chars = 0;
	i = 0;
	while (str[i])
	{
		delim = 0;
		if (str[i] == '\'' || str[i] == '\"')
		   delim = str[i++];
		//error_check = i;
		else
			i += copy_till_quotes(&v_str, &str[i]);
		if (str[i] && delim == '\'')
			i += copy_till_delim_single(&v_str, &str[i]);
		else if (str[i] && delim == '\"')
			i += copy_till_delim_double(&v_str, &str[i]);
		//if (error_check > i)
		//{
		//	free(v_str.str);
		//	return (str);
		//}
	}
	new_str = ft_strdup(v_str.str);
	free(v_str.str);
	if (!new_str)
		return (str);
	free(str);
	printf("%s\n", new_str);
	return (new_str);
}

int	expand_variables(t_token *tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tokens[i].type != -1)
	{
		tmp = expand_var_in_string(tokens[i].str);
		if (!tmp)
			return (-1);
		tokens[i++].str = tmp;
	}
	return (0);
}
