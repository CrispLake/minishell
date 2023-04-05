/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:00:45 by emajuri           #+#    #+#             */
<<<<<<< HEAD:minishell.h
/*   Updated: 2023/04/05 16:17:16 by crisplake        ###   ########.fr       */
=======
/*   Updated: 2023/04/04 13:42:54 by emajuri          ###   ########.fr       */
>>>>>>> 3a3d001fe37f0655c32a20c40911dbd4d90138cb:inc/minishell.h
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

<<<<<<< HEAD:minishell.h
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>

# define METACHARS {'|', '<', '>', ' ', '\0'}
=======
#include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
>>>>>>> 3a3d001fe37f0655c32a20c40911dbd4d90138cb:inc/minishell.h

void	rl_replace_line(const char *text, int clear_undo);
void	print_error(const char *error_message, char *input);

#endif
