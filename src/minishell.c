/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/26 14:56:09 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char			*pipeline;
	struct termios	t;
	t_token			*tokens;
	t_command		*commands;
	int				i;

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
		if (count_quotes(pipeline))
		{
			print_error("Unclosed quotes", pipeline);
			continue ;
		}
		tokens = tokenization(pipeline);
		if (!tokens)
		{
			print_error("Malloc error in tokenization", pipeline);
			continue ;
		}
		commands = make_commands(tokens);
		if (!commands)
		{
			print_error("Error in make_commands", pipeline);
			i = 0;
			while (tokens[i].str)
				free(tokens[i++].str);
			free(tokens);
			continue ;
		}
		free(tokens);
		execute_cmds(commands);
		free_commands(commands);
		free(pipeline);
	}
	return (0);
}
