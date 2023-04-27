/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:24:03 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 19:24:14 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/tokenization.h"

int	count_total(char *pipeline)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (pipeline[i])
	{
		while (ft_isspace(pipeline[i]))
			i++;
		if (!pipeline[i])
			break ;
		if (ft_strchr(METACHARS, pipeline[i]))
			i += len_metachars(&pipeline[i], pipeline[i]);
		else
			i += len_word(&pipeline[i]);
		total++;
	}
	return (total);
}

int	set_token_type(char *str)
{
	if (!str[0] || !ft_strchr(METACHARS, str[0]))
		return (WORD);
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (HEREDOC);
		return (INPUT);
	}
	else if (str[0] == '>')
	{
		if (str[1] == '>')
			return (APPEND);
		return (OUTPUT);
	}
	return (PIPE);
}

int	copy_tokens(char *pipeline, t_token *tokens, int i)
{
	int	len;
	int	token;

	len = 0;
	token = 0;
	while (pipeline[i])
	{
		while (ft_isspace(pipeline[i]))
			i++;
		if (!pipeline[i])
			break ;
		if (ft_strchr(METACHARS, pipeline[i]))
			len = len_metachars(&pipeline[i], pipeline[i]);
		else
			len = len_word(&pipeline[i]);
		tokens[token].str = ft_calloc(len + 1, sizeof(char));
		if (!tokens[token].str)
			return (-1);
		ft_strlcpy(tokens[token].str, &pipeline[i], len + 1);
		tokens[token].type = set_token_type(tokens[token].str);
		token++;
		i += len;
	}
	return (0);
}

t_token	*tokenization(char *pipeline)
{
	t_token	*tokens;
	int		count;
	int		i;

	i = 0;
	count = count_total(pipeline);
	tokens = ft_calloc(count + 1, sizeof(t_token));
	if (!tokens)
		return (NULL);
	tokens[count].type = -1;
	if (copy_tokens(pipeline, tokens, i))
	{
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		return (NULL);
	}
	return (tokens);
}
