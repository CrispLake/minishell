/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/19 19:04:41 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char			*pipeline;
	struct termios	t;
	t_token			*tokens;
	char			***commands;
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
		count_quotes(pipeline);
		//builtin_pwd();
		//builtin_export();
		//builtin_unset();
		//builtin_env();
		//builtin_echo(split);
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
		i = 0;
		while (tokens[i].str)
			free(tokens[i++].str);
		free(tokens);
		i = 0;
		while (commands[i])
			free(commands[i++]);
		free(commands);
		free(pipeline);
	}
	return (0);
}
