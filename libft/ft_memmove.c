/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:24:48 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 16:55:24 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	if (!dst && !src)
		return (0);
	if (dst > src)
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	else
		dst = ft_memcpy(dst, src, len);
	return (dst);
}
