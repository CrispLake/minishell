/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:01:29 by jole              #+#    #+#             */
/*   Updated: 2023/05/24 13:18:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <dirent.h>

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

int	cd_to_home(void)
{
	int	i;

	i = 0;
	while (g_vars.env.env[i] && ft_strncmp(g_vars.env.env[i], "HOME=", 5))
		i++;
	if (!g_vars.env.env[i])
	{
		printf("minishell: cd: HOME not set\n");
		return (-1);
	}
	if (export_to_env("OLDPWD=") == -1 || chdir(&g_vars.env.env[i][5]) || \
		export_to_env("PWD=") == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	return (0);
}

int	builtin_cd(char **args)
{
	char	*error_message;
	DIR	*d;

	if (!args[0])
		return (cd_to_home());
	d = opendir(args[0]);
	if (!d)
	{
		
		error_message = ft_strjoin("minishell: ", args[0]);
		perror(error_message);
		free(error_message);
		return (-1);
	}
	closedir(d);
	if (export_to_env("OLDPWD=") == -1 || chdir(args[0]) || \
		export_to_env("PWD=") == -1)
	{
		perror("minishell: cd");
		return (-1);
	}
	return (0);
}
