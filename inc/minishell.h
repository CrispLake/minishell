/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/13 17:49:04 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define METACHARS "|<> \t\n"

#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

void	rl_replace_line(const char *text, int clear_undo);
void	print_error(const char *error_message, char *input);

//Parsing
char	**tokenization(char *pipeline);
int		count_quotes(char *pipeline);

//Signals
void	get_signals(void);
void	close_echo_control(struct termios *t);
void	open_echo_control(struct termios *t);
void	ctrl_d_handler(void);

#endif
