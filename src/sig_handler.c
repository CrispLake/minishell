/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:21:43 by jole              #+#    #+#             */
/*   Updated: 2023/04/26 17:07:25 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_handler(int sig)
{
	sig += 0;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	get_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	close_echo_control(struct termios *t)
{
	t->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, t);
}

void	open_echo_control(struct termios *t)
{
	t->c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, t);
}

void	ctrl_d_handler(void)
{
	write(1, "\033[1A\033[13C", 9);
	write(1, "exit\n", 5);
	exit(1);
}
