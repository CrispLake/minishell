/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:01:29 by jole              #+#    #+#             */
/*   Updated: 2023/04/20 19:46:47 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_to_env(char *env)
{
	char	*str1;
	char	*str2;
	char	**split;
	char	buf[1024];

	str1 = getcwd(buf, sizeof(buf));
	if (!str1)
		return (-1);
	str2 = ft_strjoin(env, str1);
	if (!str2)
		return (-1);
	split = ft_split(str2, ' ');
	free(str2);
	if (!split)
		return (-1);
	printf("string is %s\n", split[0]);
	builtin_export(split);
	free_double_pointer(split);
	return (0);
}

int	builtin_cd(char **args)
{
	char	*error_message;

	if (!opendir(args[0]))
	{
		error_message = ft_strjoin("minishell: ", args[0]);
		perror(error_message);
		free(error_message);
		return (-1);
	}
	if (export_to_env("OLDPWD=") == -1)
	{
		perror("minishell: ");
		return (-1);
	}
	if (chdir(args[0]))
	{
		perror("minishell: ");
		return (-1);
	}
	if (export_to_env("PWD=") == -1)
	{
		perror("minishell: ");
		return (-1);
	}
	return (0);
}
