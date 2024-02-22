/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:30:11 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 16:56:08 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == NULL)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
		return ((char *)my_alloc(1));
	if (len > (unsigned int)ft_strlen(s))
		len = ft_strlen(s);
	str = my_alloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	while (s[i] && i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
