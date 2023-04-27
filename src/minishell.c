/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 14:32:38 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*parsing(char *pipeline)
{
	t_token		*tokens;
	t_command	*commands;
	int			i;

	if (count_quotes(pipeline))
	{
		print_error("Unclosed quotes", pipeline);
		return (0);
	}
	tokens = tokenization(pipeline);
	if (!tokens)
	{
		print_error("Malloc error in tokenization", pipeline);
		return (0);
	}
	if (expand_variables(tokens))
	{
		print_error("Malloc error in expand_variables", pipeline);
		i = 0;
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		return (0);
	}
	commands = make_commands(tokens);
	if (!commands)
	{
		i = 0;
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		print_error("Error in make_commands", pipeline);
		return (0);
	}
	free(tokens);
	return (commands);
}

int	main(void)
{
	char			*pipeline;
	struct termios	t;
	t_command		*commands;

	tcgetattr(0, &t);
	if (init_env())
		perror("minishell");
	increment_shlvl();
	while (1)
	{
		get_signals();
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
		if (pipeline[0] == '\0')
			continue ;
		add_history(pipeline);
		commands = parsing(pipeline);
		if (!commands)
			continue ;
		execute_cmds(commands);
		free_commands(commands);
		free(pipeline);
	}
	return (0);
}
