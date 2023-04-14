/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/14 19:13:43 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char			*pipeline;
	struct termios	t;
	t_token			*tokens;

	tcgetattr(0, &t);
	get_signals();
	while(1)
	{
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
		count_quotes(pipeline);
		tokens = tokenization(pipeline);
		if (!tokens)
			print_error("Malloc error in tokenization", pipeline);
		int	i = 0;
		printf("---\n");
		while(tokens[i].str)
		{
			printf("type: %d, %s+\n", tokens[i].type, tokens[i].str);
			i++;
		}
		printf("---\n");
		make_commands(tokens);
		free(pipeline);
	}
	return (0);
}
