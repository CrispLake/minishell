/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:18:06 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/14 16:45:11 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

enum e_tokens
{
	WORD = 0,
	PIPE = 1,
	INPUT = 2,
	OUTPUT = 3,
	HEREDOC = 4,
	APPEND = 5
};

typedef struct s_token
{
	int		type;
	char	*str;
}	t_token;

int	ft_isspace(char c);
int	len_word(char *str);
int	len_metachars(char *str, int metachar);
int	len_delim_word(char *str, int delim);

#endif
