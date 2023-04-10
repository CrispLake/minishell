/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:57:27 by jole              #+#    #+#             */
/*   Updated: 2023/04/10 13:27:35 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_to_split(char *env_var)
{
	extern char	**environ;
	int			i;
	char		*new_str;

	while (environ[j][i])
		i++;
	new_str = malloc((i + 1) * sizeof(char));
	if (!new_str)
		return (-1);
	i = 0;
	while (environ[j][i])
	{
		new_str[i] = environ[j][i];
		i++;
	}
	new_str[i] = '\0';
	env_var = new_str;
	return (0);
}

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
	while (ft_strncmp(environ[j], &input[command][i], len) && environ[j] \
			&& ft_strncmp(environ[j], "_=/Users", 8) != 0)
		j++;
	if (ft_strncmp(environ[j], &input[command][1], len) == 0)
	{
		printf("found env var\n");
		return (j);
	}
	printf("did not find env var\n");
	return (-1);
}

int	expand_variables(char **input)
{
	int	i;
	int	j;
	int	command;

	i = 0;
	j = 0;
	command = 0;
	while (input[command])
	{
		while (input[command][i])
		{
			if (input[command][i] == '$')
			{
				j = check_if_env_var(input, command, i + 1);
				if (j == -1)
					break ;
				if (expand_to_split(input[command], j) == -1)
					return (-1);
			}
			i++;
		}
		i = 0;
		command++;
	}
	return (0);
}
