/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emajuri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:13:18 by emajuri           #+#    #+#             */
/*   Updated: 2023/04/05 18:24:41 by crisplake        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"
#include <unistd.h>

static int	putull_base(unsigned long long n, int base, int caps, int fd)
{
	const char	*str = "0123456789abcdef0123456789ABCDEF";
	int			count;

	if (caps)
		str += 16;
	count = 0;
	if (base < 2 || base > 16)
		return (0);
	if (n > (unsigned int)(base - 1))
	{
		count += putull_base(n / base, base, caps, fd);
		count += putull_base(n % base, base, caps, fd);
	}
	if (n <= (unsigned int)(base - 1))
	{
		ft_putchar_fd(str[n], fd);
		return (++count);
	}
	return (count);
}

static int	putnbr_base_count(int n, int base, char *str, int fd)
{
	long	nb;
	int		count;

	count = 1;
	nb = n;
	if (nb < 0)
	{
		count++;
		ft_putchar_fd('-', 1);
		nb = nb * -1;
	}
	if (nb >= base)
	{
		count += putnbr_base_count(nb / base, base, str, fd);
		ft_putchar_fd(str[nb % base], fd);
		return (count);
	}
	if (nb < base)
	{
		ft_putchar_fd(str[nb % base], fd);
		return (count);
	}
	return (0);
}

static int	convert2(const char *str, va_list ap, int fd)
{
	int	len;

	len = 1;
	if (*str == 'p')
	{
		write(1, "0x", 2);
		len += 1;
		len += putull_base((unsigned long long)va_arg(ap, char *), 16, 0, fd);
	}
	else if (*str == 'd' || *str == 'i')
		len = putnbr_base_count(va_arg(ap, int), 10, "0123456789abcdef", fd);
	else if (*str == 'u')
		len = putull_base(va_arg(ap, unsigned int), 10, 0, fd);
	else if (*str == 'x')
		len = putull_base(va_arg(ap, unsigned int), 16, 0, fd);
	else if (*str == 'X')
		len = putull_base(va_arg(ap, unsigned int), 16, 1, fd);
	else if (*str == '%')
		ft_putchar_fd('%', fd);
	return (len);
}

static int	convert(const char *str, va_list ap, int fd)
{
	int		len;
	char	*tmp;

	len = 1;
	if (*str == 'c')
		ft_putchar_fd(va_arg(ap, int), fd);
	else if (*str == 's')
	{
		tmp = va_arg(ap, char *);
		if (!tmp)
		{
			write(1, "(null)", 6);
			len = 6;
		}
		else
		{
			len = ft_strlen(tmp);
			ft_putstr_fd(tmp, fd);
		}
	}
	else
		return (convert2(str, ap, fd));
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			len += convert(str, ap, fd);
			if (*str)
				str++;
		}
		else
		{
			ft_putchar_fd(*str, fd);
			str++;
			len++;
		}
	}
	va_end(ap);
	return (len);
}
