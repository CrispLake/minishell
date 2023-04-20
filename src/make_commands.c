/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:22:21 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/18 11:14:21 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	error_print(int error)
{
	char	c;

	if (error == PIPE)
		c = '|';
	else if (error == INPUT || error == HEREDOC)
		c = '<';
	else
		c = '>';
	printf("minishell: syntax error near unexpected token '%c'\n", c);
	return (-1);
}

static int	count_commands(t_token *tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (tokens[i].str)
	{
		if (!i && tokens[i].type == PIPE)
			return (error_print(PIPE));
		if (tokens[i].type == PIPE)
		{
			if (tokens[i + 1].type == PIPE || tokens[i + 1].type == -1)
				return (error_print(PIPE));
			count++;
		}
		else if (tokens[i].type != WORD)
			if (tokens[i + 1].type != WORD)
				return (error_print(tokens[i].type));
		i++;
	}
	return (count);
}

t_command	*make_commands(t_token *tokens)
{
	t_command	*commands;
	int			count;
	int			i;

	count = count_commands(tokens);
	if (count < 0)
		return (NULL);
	commands = ft_calloc(count + 1, sizeof(t_command));
	if (!commands)
		return (NULL);
	if (place_pointers(commands, tokens))
	{
		i = 0;
		while (commands[i].cmd)
			free(commands[i++].cmd);
		i = 0;
		while (commands[i].redi)
			free(commands[i++].redi);
		free(commands);
		return (NULL);
	}
	return (commands);
}
