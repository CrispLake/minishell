/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:36:11 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/27 19:16:43 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("---\n");
	while (tokens[i].type != -1)
	{
		printf("type: %d, %s+\n", tokens[i].type, tokens[i].str);
		i++;
	}
	printf("type: %d, %s+\n", tokens[i].type, tokens[i].str);
	printf("---\n");
}

void	print_commands(t_command *commands)
{
	int	i;
	int	i2;

	printf("\n@@@@@@@@@@@@@\n\n");
	i = 0;
	while (commands[i].cmd || commands[i].redi)
	{
		i2 = 0;
		printf("command: %d: \n", i);
		while (commands[i].cmd[i2])
		{
			printf("%s\n", commands[i].cmd[i2]);
			i2++;
		}
		i2 = 0;
		printf("redis: \n");
		if (commands[i].redi)
		{
			while (commands[i].redi[i2])
			{
				printf("%s\n", commands[i].redi[i2]);
				i2++;
			}
		}
		i++;
		printf("\n");
	}
	printf("\n@@@@@@@@@@@@@\n\n");
}
