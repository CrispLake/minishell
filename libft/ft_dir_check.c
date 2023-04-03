/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:05:29 by emajuri           #+#    #+#             */
/*   Updated: 2023/02/07 14:28:09 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

int	ft_dir_check(char *filename)
{
	char	buf[1];
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read(fd, buf, 1) == -1)
	{
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}
