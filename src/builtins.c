/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:12:55 by jole              #+#    #+#             */
/*   Updated: 2023/04/14 16:04:37 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Error in getcwd");
		return (-1);
	}
	return (0);
}

void	builtin_env(void)
{
	int	i;

	i = 0;
	while (environ[i])
		printf("%s\n", environ[i++]);
}

void	builtin_export(char *str)
{
	
}
