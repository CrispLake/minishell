/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:00:43 by jole              #+#    #+#             */
/*   Updated: 2023/04/14 20:37:47 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_quotes(char *pipeline)
{
	int	i;
	int	delim;

	i = 0;
	delim = 0;
	while (pipeline[i])
	{
		if (pipeline[i] == '\'' || pipeline [i] == '\"')
		{
			delim = pipeline[i];
			while (pipeline[i++])
			{
				if (pipeline[i] == delim)
				{
					delim = 0;
					break ;
				}
			}
			if (delim != 0)
				return (1);
		}
		i++;
	}
	return (0);
}
