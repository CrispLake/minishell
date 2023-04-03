/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putull_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 09:58:30 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/03 19:50:20 by emajuri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putull_base_fd(unsigned long long n, int base, int fd)
{
	const char	*str = "0123456789abcdefg";

	if (base < 2 || base > 16)
		return ;
	if (n > (unsigned long long)(base - 1))
	{
		ft_putull_base_fd(n / base, base, fd);
		ft_putull_base_fd(n % base, base, fd);
	}
	if (n <= (unsigned long long)(base - 1))
		ft_putchar_fd(str[n], fd);
}
