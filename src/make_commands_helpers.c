/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:15:56 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/17 16:17:25 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_type(t_token *tokens, int type)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != -1)
	{
		if (!i && tokens[i].type == type)
			count++;
		else if (i)
		{
			if (type == WORD)
			{
				if (tokens[i - 1].type == WORD || tokens[i - 1].type == PIPE)
					count++;
			}
			else
			{
				if (tokens[i].type == type || tokens[i - 1].type == type)
					count++;
			}
		}
		i++;
	}
	return (count);
}

static void	point_words(char **commands, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != -1)
	{
		while (tokens[i].type == WORD)
		{
			if (i)
				if (tokens[i - 1].type != WORD && tokens[i - 1].type != PIPE)
					break ;
			*commands = tokens[i].str;
			commands++;
			break ;
		}
		i++;
	}
	commands = NULL;
}

static void	point_redirections(char **commands, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != -1)
	{
		if (tokens[i].type != WORD)
		{
			*commands = tokens[i].str;
			commands++;
		}
		else if (i)
		{
			if (tokens[i].type == WORD && \
				(tokens[i - 1].type != PIPE && tokens[i - 1].type != WORD))
			{
				*commands = tokens[i].str;
				commands++;
			}
		}
		i++;
	}
	commands = NULL;
}

int	place_pointers(char ***commands, t_token *tokens)
{
	int	i;
	int	tok;

	i = 0;
	tok = 0;
	while (tokens[tok].str)
	{
		commands[i] = ft_calloc(count_type(&tokens[tok], WORD) + 1, \
						sizeof(char *));
		if (!commands[i])
			return (-1);
		commands[i + 1] = ft_calloc(count_type(&tokens[tok], INPUT) + \
						count_type(&tokens[tok], OUTPUT) + \
						count_type(&tokens[tok], HEREDOC) + \
						count_type(&tokens[tok], APPEND) + 1, sizeof(char *));
		if (!commands[i + 1])
			return (-1);
		point_words(commands[i], &tokens[tok]);
		point_redirections(commands[i + 1], &tokens[tok]);
		while (tokens[tok].type != PIPE && tokens[tok + 1].type != -1)
			tok++;
		tok++;
		i += 2;
	}
	return (0);
}
