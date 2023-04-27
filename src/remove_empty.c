/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_empty.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:25:32 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 17:02:05 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	copy_tokens_if_exist(t_token *tokens, t_token *copy)
{
	int		i;
	int		i2;

	i = 0;
	i2 = 0;
	while (tokens[i].str)
	{
		if (tokens[i].str[0])
		{
			copy[i2].str = tokens[i].str;
			copy[i2].type = tokens[i].type;
			i2++;
		}
		else
			free(tokens[i].str);
		i++;
	}
}

t_token	*remove_empty(t_token *tokens)
{
	t_token	*copy;
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (tokens[++i].str)
		if (tokens[i].str[0])
			count++;
	copy = ft_calloc(count + 1, sizeof(t_token));
	if (!copy)
	{
		free_tokens(tokens);
		return (NULL);
	}
	copy[count].type = -1;
	copy_tokens_if_exist(tokens, copy);
	free(tokens);
	return (copy);
}
