/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/14 15:18:10 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv)
{
	char	*pipeline;
	struct termios t;

	argc += 0;
	argv += 0;
	tcgetattr(0, &t);
	get_signals();
	int i = 0;
	while (environ[i])
		i++;
	i -= 2;
	printf("%s\n", environ[i]);
	environ[i][5] = 'E';
	printf("%s\n", environ[i]);
	i = 0;
	while (environ[i])
		free(environ[i++]);
	while(1)
	{
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
		count_quotes(pipeline);
		//builtin_pwd();
		//builtin_env();
		free(pipeline);
	}
	return (0);
}
