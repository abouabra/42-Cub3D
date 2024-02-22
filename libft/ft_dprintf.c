/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 17:34:12 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 17:34:15 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	adress_helper(unsigned long long nb, int *tracker, int fd)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
	{
		adress_helper(nb / 16, tracker, fd);
		adress_helper(nb % 16, tracker, fd);
	}
	else
		ft_dputchar(base[nb % 16], tracker, fd);
}

void	ft_dput_adress(void *ptr, int *tracker, int fd)
{
	unsigned long long	nb;

	nb = (unsigned long long)ptr;
	ft_dputstr("0x", tracker, fd);
	adress_helper(nb, tracker, fd);
}

void	print_specifiers(va_list args, char str, int *tracker, int fd)
{
	if (str == 'c')
		ft_dputchar(va_arg(args, int), tracker, fd);
	if (str == '%')
		ft_dputchar('%', tracker, fd);
	if (str == 's')
		ft_dputstr(va_arg(args, char *), tracker, fd);
	if (str == 'd' || str == 'i')
		ft_dputnbr(va_arg(args, int), tracker, fd);
	if (str == 'u')
		ft_dput_unsigned_nbr(va_arg(args, unsigned int), tracker, fd);
	if (str == 'x')
		ft_dput_hex_nbr(va_arg(args, unsigned int), 'x', tracker, fd);
	if (str == 'X')
		ft_dput_hex_nbr(va_arg(args, unsigned int), 'X', tracker, fd);
	if (str == 'p')
		ft_dput_adress(va_arg(args, void *), tracker, fd);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	int		tracker;
	va_list	args;

	va_start(args, str);
	tracker = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			print_specifiers(args, *str, &tracker, fd);
		}
		else
			ft_dputchar(*str, &tracker, fd);
		str++;
	}
	va_end(args);
	return (tracker);
}
