/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/14 22:51:13 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "tokenization.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# define METACHARS "|<> \t\n"

void	rl_replace_line(const char *text, int clear_undo);
void	print_error(const char *error_message, char *input);

//Parsing
t_token	*tokenization(char *pipeline);
int		count_quotes(char *pipeline);
char	***make_commands(t_token *tokens);

//Signals
void	get_signals(void);
void	close_echo_control(struct termios *t);
void	open_echo_control(struct termios *t);
void	ctrl_d_handler(void);

#endif
