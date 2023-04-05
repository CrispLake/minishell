/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/05 18:48:17 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*pipeline;
	struct	termios t;

	tcgetattr(0, &t);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		pipeline = readline("minishell ~>");
		t.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		if (!pipeline)
			break ;
		free(pipeline);
	}
	return (0);
}
