/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:46 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 16:55:24 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *str, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		if (((unsigned char *)str)[i] == ((unsigned char)c))
			return ((void *)(str + i));
	return (0);
}
