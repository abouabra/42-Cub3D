/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:37:20 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 17:34:21 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputchar(char c, int *tracker, int fd)
{
	write(fd, &c, 1);
	(*tracker)++;
}

void	ft_dputnbr(int n, int *tracker, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = nb * -1;
		ft_dputchar('-', tracker, fd);
	}
	if (nb > 9)
	{
		ft_dputnbr(nb / 10, tracker, fd);
		ft_dputnbr(nb % 10, tracker, fd);
	}
	else
		ft_dputchar(nb + '0', tracker, fd);
}

void	ft_dputstr(char *s, int *tracker, int fd)
{
	int	i;

	i = 0;
	if (!s)
		s = "(null)";
	while (s[i])
	{
		ft_dputchar(s[i], tracker, fd);
		i++;
	}
}

void	ft_dput_unsigned_nbr(unsigned int nb, int *tracker, int fd)
{
	if (nb >= 10)
	{
		ft_dput_unsigned_nbr(nb / 10, tracker, fd);
		ft_dput_unsigned_nbr(nb % 10, tracker, fd);
	}
	else
		ft_dputchar(nb + '0', tracker, fd);
}

void	ft_dput_hex_nbr(unsigned int nb, char x, int *tracker, int fd)
{
	char	*base;

	if (x == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_dput_hex_nbr(nb / 16, x, tracker, fd);
		ft_dput_hex_nbr(nb % 16, x, tracker, fd);
	}
	else
		ft_dputchar(base[nb % 16], tracker, fd);
}
