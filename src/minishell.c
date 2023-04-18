/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/18 11:02:28 by emajuri          ###   ########.fr       */
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
	get_signals();
	init_env();
	while (1)
	{
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
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
		print_commands(commands);
		i = 0;
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		i = 0;
		while (commands[i].cmd)
			free(commands[i++].cmd);
		i = 0;
		while (commands[i].redi)
			free(commands[i++].redi);
		free(commands);
		free(pipeline);
	}
	return (0);
}
