/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:25:27 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 16:55:24 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	x;
	size_t	y;

	if (dst == NULL && size == 0)
		return (0);
	i = ft_strlen(dst);
	j = ft_strlen(src);
	if (size <= i)
		return (size + j);
	x = i;
	y = 0;
	while (src[y] && i < size - 1)
	{
		dst[i] = src[y];
		i++;
		y++;
	}
	dst[i] = 0;
	return (x + j);
}
