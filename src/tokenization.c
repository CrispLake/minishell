/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:24:03 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/12 19:30:51 by crisplake        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

int	len_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(METACHARS, str[i]) && str[i])
		i++;
	return (i);
}

int	len_metachars(char *str, int metachar)
{
	int	i;

	i = 0;
	while (str[i] == metachar)
		i++;
	return (i);
}

int	len_delim_word(char *str, int delim)
{
	int	i;

	i = 0;
	while (str[i] != delim)
		i++;
	return (i);
}

int	count_total(char *pipeline)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (pipeline[i])
	{
		if (ft_strchr("\'\"", pipeline[i]))
			i += len_delim_word(&pipeline[i], pipeline[i]);
		else if (ft_strchr(METACHARS, pipeline[i]))
			i += len_metachars(&pipeline[i], pipeline[i]);
		else
			i += len_word(&pipeline[i]);
		if (ft_isspace(pipeline[i - 1]))
			total--;
		total++;
	}
	return (total);
}

int	copy_tokens(char *pipeline, char **tokens)
{
	int	i;
	int	len;
	int	token;

	i = 0;
	len = 0;
	token = 0;
	while (pipeline[i])
	{
		while (ft_isspace(pipeline[i]))
			i++;
		if (ft_strchr("\'\"", pipeline[i]))
			len = len_delim_word(&pipeline[i], pipeline[i]);
		else if (ft_strchr(METACHARS, pipeline[i]))
			len = len_metachars(&pipeline[i], pipeline[i]);
		else
			len = len_word(&pipeline[i]);
		tokens[token] = ft_calloc(len + 1, sizeof(char));
		if (!tokens[token])
			return (-1);
		ft_strlcpy(tokens[token], &pipeline[i], len + 1);
		token++;
		i += len;
	}
	return (0);
}

char	**tokenization(char *pipeline)
{
	char	**tokens;
	int		count;
	int		i;

	i = 0;
	count = count_total(pipeline);
	tokens = ft_calloc(count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	tokens[count] = NULL;
	if (copy_tokens(pipeline, tokens))
	{
		while (tokens[i])
			free(tokens[i++]);
		free(tokens);
		return (NULL);
	}
	return (tokens);
}
