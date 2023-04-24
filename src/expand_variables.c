/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:05:50 by jole              #+#    #+#             */
/*   Updated: 2023/04/24 21:40:17 by jole             ###   ########.fr       */
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

int	if_env_expand(t_vector *v_str, char *str, int len)
{
	int	i;
	int	x;

	i = 0;
	x = len + 1;
	while (g_vars.env.env[i])
	{
		if (!ft_strncmp(g_vars.env.env[i], str, len) && g_vars.env.env[i][len] == '=')
		{
			printf("env found: %s\n", g_vars.env.env[i]);
			while (g_vars.env.env[i][x])
			{
				if (v_str->chars + 2 > v_str->size)
					expand_vector(v_str);
				v_str->str[v_str->chars++] = g_vars.env.env[i][x++];
			}
			return (len);
		}
		i++;
	}
	printf("string in if env expand: %s\n", v_str->str);
	return (-1);
}

int	copy_till_quotes(t_vector *v_str, char *str)
{
	int	i;
	int	len;

	i = 0;
	printf("string in copy till quotes: %s\n", str);
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
	printf("skipping %d in single\n", i + 1);
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
	printf("skipping %d in double\n", i + 1);
	return (i + 1);
}

char	*expand_var_in_string(char *str)
{
	t_vector	v_str;
	//char		*new_str;
	int			i;
	int			delim;

	v_str.size = 50;
	v_str.str = ft_calloc(v_str.size, sizeof(char));
	v_str.chars = 0;
	i = 0;
	while (str[i])
	{
		printf("pointing to: %s\n", &str[i]);
		delim = 0;
		if (str[i] == '\'' || str[i] == '\"')
		   delim = str[i++];
		else 
			i += copy_till_quotes(&v_str, &str[i]);
		if (str[i] && delim == '\'')
		{
			printf("going to \'function\n");
			i += copy_till_delim_single(&v_str, &str[i]);
		}
		else if (str[i] && delim == '\"')
		{
			printf("going to \" function\n");
			i += copy_till_delim_double(&v_str, &str[i]);
		}
	}
	v_str.str[v_str.chars] = '\0';
	printf("string after everything: %s\n", v_str.str);
	return (NULL);
}
