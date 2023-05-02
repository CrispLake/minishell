/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:52:42 by jole              #+#    #+#             */
/*   Updated: 2023/05/02 17:22:13 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	print_error(const char *error_message, char *input)
{
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	free(input);
	return (0);
}

void	free_double_pointer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

int	increment_shlvl(void)
{
	int		i;
	char	*str;
	char	*str2;

	i = 0;
	while (g_vars.env.env[i] && ft_strncmp(g_vars.env.env[i], "SHLVL=", 6))
		i++;
	if (!g_vars.env.env[i])
		export_string("SHLVL=1");
	str = ft_itoa(ft_atoi(&g_vars.env.env[i][6]) + 1);
	if (!str)
		return (-1);
	str2 = ft_strjoin("SHLVL=", str);
	free(str);
	if (!str2)
		return (-1);
	export_string(str2);
	free(str2);
	return (0);
}

void	free_commands(t_command *commands)
{
	int	i;
	int	i2;

	i = 0;
	while (commands[i].cmd || commands[i].redi)
	{
		i2 = 0;
		while (commands[i].cmd[i2])
			free(commands[i].cmd[i2++]);
		i2 = 0;
		while (commands[i].redi[i2])
			free(commands[i].redi[i2++]);
		free(commands[i].cmd);
		free(commands[i].redi);
		i++;
	}
	free(commands);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].str)
		free(tokens[i++].str);
	free(tokens);
}
