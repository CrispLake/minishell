/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 20:24:03 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/05 18:37:29 by crisplake        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	len_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr(METACHARS, str[i]) && str[i])
		i++;
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

int	count_total(char *pipeline)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (pipeline[i])
	{
		if (ft_strchr("'\"", pipeline[i]))
			i += len_delim_word(&pipeline[i], pipeline[i]);
		else if (ft_strchr(METACHARS, pipeline[i]))
			i += len_metachars(&pipeline[i], pipeline[i]);
		else
			i += len_word(&pipeline[i]);
		if (pipeline[i - 1] == ' ')
			total--;
		total++;
	}
	return (total);
}

char	**tokenization(char *pipeline)
{
	char **tokens;

	tokens = ft_calloc(count_total(pipeline), sizeof(char *));
	if (!tokens)
		return (NULL);
	return (0);
}
