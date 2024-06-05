/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:21:43 by jole              #+#    #+#             */
/*   Updated: 2024/06/04 19:56:14 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <sys/ioctl.h>

void	sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
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
	write(1, "exit\n", 5);
	exit(1);
}
