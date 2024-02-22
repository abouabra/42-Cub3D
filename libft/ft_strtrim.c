/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:53:46 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 16:55:24 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char *s1, char *set)
{
	int	i;
	int	j;

	if (s1 == NULL || set == NULL)
		return (0);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	if (!s1[i])
		return (ft_substr(s1, i, 0));
	while (s1[j] && ft_strchr(set, s1[j]))
		j--;
	if (j == -1)
		return (ft_substr(s1, i, 0));
	return (ft_substr(s1, i, (j - i + 1)));
}
