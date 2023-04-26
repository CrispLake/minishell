/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/26 15:47:02 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(char *pipeline)
{
	t_token		*tokens;
	t_command	*commands;
	int			i;

	if (count_quotes(pipeline))
		return (print_error("Unclosed quotes", pipeline));
	tokens = tokenization(pipeline);
	if (!tokens)
		return (print_error("Malloc error in tokenization", pipeline));
	commands = make_commands(tokens);
	if (!commands)
	{
		i = 0;
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		return (print_error("Error in make_commands", pipeline));
	}
	free(tokens);
	return (0);
}

int	main(void)
{
	char			*pipeline;
	struct termios	t;
	t_command		*commands;

	tcgetattr(0, &t);
	if (init_env())
		perror("minishell");
	while (1)
	{
		get_signals();
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
		add_history(pipeline);
		if (parsing(pipeline))
			continue ;
		execute_cmds(commands);
		free_commands(commands);
		free(pipeline);
	}
	return (0);
}
