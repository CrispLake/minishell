/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:57:27 by jole              #+#    #+#             */
/*   Updated: 2023/04/10 14:29:50 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	expand_to_split(char **env_var, int j)
{
	extern char	**environ;
	int			i;

	i = 0;
	free(env_var[0]);
	while (environ[j][i])
		i++;
	env_var[0] = malloc((i + 1) * sizeof(char));
	if (!env_var[0])
		return (-1);
	i = 0;
	while (environ[j][i])
	{
		env_var[0][i] = environ[j][i];
		i++;
	}
	env_var[0][i] = '\0';
	return (0);
}

int	check_if_env_var(char **input, int var, int i)
{
	extern char	**environ;
	int			len;
	int 		j;

	len = 0;
	j = i;
	while (input[var][j])
	{
		if (input[var][j] == ' ' || input[var][j] == '\0')
			break ;
		j++;
		len++;
	}
	j = 0;
	while (ft_strncmp(environ[j], &input[var][i], len) && environ[j] \
			&& ft_strncmp(environ[j], "_=/Users", 8) != 0)
		j++;
	if (ft_strncmp(environ[j], &input[var][1], len) == 0)
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
	int	var;

	i = 0;
	j = 0;
	var = 0;
	while (input[var])
	{
		while (input[var][i])
		{
			if (input[var][i] == '$')
			{
				j = check_if_env_var(input, var, i + 1);
				if (j == -1)
					break ;
				if (expand_to_split(&input[var], j) == -1)
					return (-1);
			}
			i++;
		}
		i = 0;
		var++;
	}
	return (0);
}
