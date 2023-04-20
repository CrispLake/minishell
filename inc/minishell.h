/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/20 17:53:50 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "tokenization.h"
# include "execution.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# define METACHARS "|<> \t\n"

//Debug
void		print_tokens(t_token *tokens);
void		print_commands(t_command *commands);
//endofdebug

typedef struct s_env
{
	char	**env;
	int		size;
	int		items;
}				t_env;

typedef struct s_vars
{
	t_env	env;
	int		last_exit;
}				t_vars;

t_vars		g_vars;

int			init_env(void);
void		rl_replace_line(const char *text, int clear_undo);
void		print_error(const char *error_message, char *input);
void	free_double_pointer(char **array);

//Parsing
t_token		*tokenization(char *pipeline);
int			count_quotes(char *pipeline);
t_command	*make_commands(t_token *tokens);
int			place_pointers(t_command *commands, t_token *tokens);

//Signals
void		get_signals(void);
void		close_echo_control(struct termios *t);
void		open_echo_control(struct termios *t);
void		ctrl_d_handler(void);

int		count_quotes(char *pipeline);

//Builtins
int		builtin_pwd(void);
int		builtin_env(void);
int		builtin_export(char **args);
int		builtin_unset(char **args);
int		builtin_echo(char **args);
int		builtin_exit(char **args);

#endif