/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:17:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/13 17:34:50 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	if (c == '\t')
		return (1);
	if (c == '\n')
		return (1);
	return (0);
}

int	is_number(char *str, int i)
{
	int	i2;

	i2 = 0;
	while (i2 < i)
	{
		if (!ft_isdigit(str[i2++]))
			return (0);
	}
	return (1);
}

int	len_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(METACHARS, str[i]) && str[i])
		i++;
	if (str[i] == '<' || str[i] == '>')
	{
		if (is_number(str, i))
		{
			while (str[i] == '<' || str[i] == '>')
				i++;
		}
	}
	return (i);
}

int	len_metachars(char *str, int metachar)
{
	int	i;

	i = 0;
	while (str[i] == metachar)
		i++;
	return (i);
}

int	len_delim_word(char *str, int delim)
{
	int	i;

	i = 0;
	while (str[i] != delim)
		i++;
	return (i);
}
