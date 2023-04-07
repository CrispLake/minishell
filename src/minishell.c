/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:01:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/07 16:47:45 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	char	*pipeline;
	struct termios t;

	tcgetattr(0, &t);
	get_signals();
	while(1)
	{
		close_echo_control(&t);
		pipeline = readline("minishell ~>");
		open_echo_control(&t);
		if (!pipeline)
			ctrl_d_handler();
		free(pipeline);
	}
	return (0);
}
