/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:15:56 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/18 12:36:08 by emajuri          ###   ########.fr       */
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

static int	count_redi(t_token *tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != -1)
	{
		if (!i && (tokens[i].type != WORD && tokens[i].type != PIPE))
			count++;
		else if (i)
		{
			if (tokens[i].type != WORD && tokens[i].type != PIPE)
				count++;
			else if (tokens[i - 1].type != WORD && tokens[i - 1].type != PIPE)
				count++;
		}
		i++;
	}
	return (count);
}

static void	point_words(char **cmd, t_token *tokens)
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
			*cmd = tokens[i].str;
			cmd++;
			break ;
		}
		i++;
	}
	cmd = NULL;
}

static void	point_redirections(char **redi, t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != PIPE && tokens[i].type != -1)
	{
		if (tokens[i].type != WORD)
		{
			*redi = tokens[i].str;
			redi++;
		}
		else if (i)
		{
			if (tokens[i].type == WORD && \
				(tokens[i - 1].type != PIPE && tokens[i - 1].type != WORD))
			{
				*redi = tokens[i].str;
				redi++;
			}
		}
		i++;
	}
	redi = NULL;
}

int	place_pointers(t_command *cmds, t_token *tokens)
{
	int	i;
	int	tok;

	i = 0;
	tok = 0;
	while (tokens[tok].str)
	{
		cmds[i].cmd = ft_calloc(count_type(&tokens[tok], WORD) + 1, \
						sizeof(char *));
		if (!cmds[i].cmd)
			return (-1);
		cmds[i].redi = ft_calloc(count_redi(&tokens[tok]) + 1, sizeof(char *));
		if (!cmds[i].redi)
			return (-1);
		point_words(cmds[i].cmd, &tokens[tok]);
		point_redirections(cmds[i].redi, &tokens[tok]);
		while (tokens[tok].type != PIPE && tokens[tok].type != -1)
			tok++;
		if (tokens[tok].type == PIPE)
			tok++;
		i++;
	}
	return (0);
}
