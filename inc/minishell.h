/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:45 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 19:52:07 by emajuri          ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>
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
}	t_env;

typedef struct s_vector
{
	char	*str;
	int		size;
	int		chars;
}				t_vector;

typedef struct s_vars
{
	t_env	env;
	int		last_exit;
	int		status;
}	t_vars;

t_vars		g_vars;

int			init_env(void);
void		rl_replace_line(const char *text, int clear_undo);
int			print_error(const char *error_message, char *input);
void		free_double_pointer(char **array);
int			increment_shlvl(void);
int			expand_variables(t_token *tokens, int i);
void		free_commands(t_command *commands);

//Parsing
t_token		*tokenization(char *pipeline);
int			count_quotes(char *pipeline);
t_command	*make_commands(t_token *tokens);
int			place_pointers(t_command *commands, t_token *tokens);
t_token		*remove_empty(t_token *tokens);

//Expand
int			expand_vector(t_vector *v_str);
int			expand_dollar(t_vector *v_str);
int			if_env_expand(t_vector *v_str, char *str, int len, int i);
int			init_vector(t_vector *v_str);
int			copy_char(t_vector *v_str, char *str, int *i);

//Signals
void		get_signals(void);
void		close_echo_control(struct termios *t);
void		open_echo_control(struct termios *t);
void		ctrl_d_handler(void);
void		sigint_heredoc(int sig);

//Builtins
int			builtin_echo(char **args);
int			builtin_cd(char **args);
int			builtin_pwd(void);
int			builtin_export(char **args);
int			builtin_unset(char **args);
int			builtin_env(void);
int			builtin_exit(char **args);
int			export_string(char *str);

#endif
