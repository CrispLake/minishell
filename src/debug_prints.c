/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:36:11 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/17 16:42:08 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("---\n");
	while (tokens[i].str)
	{
		printf("type: %d, %s+\n", tokens[i].type, tokens[i].str);
		i++;
	}
	printf("---\n");
}

void	print_commands(char ***commands)
{
	int	i;
	int	i2;

	printf("\n@@@@@@@@@@@@@\n\n");
	i = 0;
	while (commands[i])
	{
		i2 = 0;
		printf("%d: \n", i);
		while (commands[i][i2])
		{
			printf("%s\n", commands[i][i2]);
			i2++;
		}
		i++;
		printf("\n");
	}
	printf("\n@@@@@@@@@@@@@\n\n");
}
