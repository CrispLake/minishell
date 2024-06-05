/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 20:42:28 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_vars g_vars;

t_token	*create_tokens(char *pipeline)
{
	t_token	*tokens;

	tokens = tokenization(pipeline);
	if (!tokens)
	{
		print_error("Malloc error in tokenization", pipeline);
		return (NULL);
	}
	if (expand_variables(tokens, 0))
	{
		print_error("Malloc error in expand_variables", pipeline);
		free_tokens(tokens);
		return (NULL);
	}
	tokens = remove_empty(tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}

t_command	*parsing(char *pipeline)
{
	t_token		*tokens;
	t_command	*commands;

	if (count_quotes(pipeline))
	{
		print_error("Unclosed quotes", pipeline);
		return (NULL);
	}
	tokens = create_tokens(pipeline);
	if (!tokens)
		return (NULL);
	commands = make_commands(tokens);
	free(pipeline);
	if (!commands)
	{
		free_tokens(tokens);
		return (NULL);
	}
	free(tokens);
	return (commands);
}

int	main(void)
{
	struct termios	t;
	t_command		*commands;
	char			*pipeline;

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
	}
	return (0);
}
