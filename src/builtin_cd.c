/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:01:29 by jole              #+#    #+#             */
/*   Updated: 2023/04/21 13:31:36 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	export_to_env(char *env)
{
	char	*str1;
	char	*str2;
	char	buf[1024];

	str1 = getcwd(buf, sizeof(buf));
	if (!str1)
		return (-1);
	str2 = ft_strjoin(env, str1);
	if (!str2)
		return (-1);
	export_string(str2);
	free(str2);
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
		perror("minishell: cd");
		return (-1);
	}
	if (chdir(args[0]))
	{
		perror("minishell: cd");
		return (-1);
	}
	if (export_to_env("PWD=") == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	return (0);
}
