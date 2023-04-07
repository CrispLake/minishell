/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:57:27 by jole              #+#    #+#             */
/*   Updated: 2023/04/07 21:44:14 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_if_env_var(char **input, int command, int i)
{
	extern char	**environ;
	int			len;
	int 		j;

	len = 0;
	j = i;
	while (input[command][j])
	{
		if (input[command][j] == ' ' || input[command][j] == '\0')
			break ;
		j++;
		len++;
	}
	j = 0;
	printf("len: %d\n", len);
	while (ft_strncmp(environ[j], &input[command][i], len) && environ[j] \
			&& ft_strncmp(environ[j], "_=/Users", 8) != 0)
	{
		printf("comparing: %s\n", input[command]);
		printf("to: %s\n", environ[j]);
		if (ft_strncmp(environ[j], &input[command][i], len) == 0)
		{
			printf("found env var\n");
			return (0);
		}
		j++;
	}
	printf("did not find env var\n");
	if (!environ[j])
		return (-1);
	return (-1);
}

int	expand_variables(char **input)
{
	int	i;
	int	command;

	i = 0;
	command = 0;
	while (input[command])
	{
		while (input[command][i])
		{
			if (input[command][i] == '$')
				check_if_env_var(input, command, i + 1);
			i++;
		}
		i = 0;
		command++;
	}
	return (0);
}
