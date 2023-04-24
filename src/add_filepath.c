/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_filepath.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <emajuri@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 20:35:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/24 16:36:17 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**get_paths(void)
{
	char	**paths;
	int		i;

	i = 0;
	while (g_vars.env.env[i] && ft_strncmp(g_vars.env.env[i], "PATH=", 5))
		i++;
	if (!g_vars.env.env[i])
		return (NULL);
	paths = ft_split(&g_vars.env.env[i][5], ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*add_str_to_path(char *path, char *str)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(path, "/");
	if (!tmp1)
		return (NULL);
	tmp2 = ft_strjoin(tmp1, str);
	free(tmp1);
	if (!tmp2)
		return (NULL);
	return (tmp2);
}

static int	test_paths(char **cmd)
{
	char	**paths;
	int		i;
	char	*full;

	paths = get_paths();
	i = -1;
	while (paths[++i])
	{
		full = add_str_to_path(paths[i], cmd[0]);
		if (!full)
		{
			free_double_pointer(paths);
			return (-1);
		}
		if (!access(full, F_OK | R_OK | X_OK))
		{
			free_double_pointer(paths);
			free(cmd[0]);
			cmd[0] = full;
			return (0);
		}
		free(full);
	}
	free_double_pointer(paths);
	return (-1);
}

int	add_filepath(char **cmd)
{
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], F_OK) || access(cmd[0], R_OK | X_OK))
		{
			perror("minishell: COMMAND HERE SOMEHOW");
			return (-1);
		}
	}
	else if (!check_for_builtin(cmd[0]) && test_paths(cmd))
	{
		perror("minishell: COMMAND HERE SOMEHOW");
		return (-1);
	}
	return (0);
}
