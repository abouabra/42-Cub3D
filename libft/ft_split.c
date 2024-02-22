/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:38:10 by abouabra          #+#    #+#             */
/*   Updated: 2023/01/20 17:14:11 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_count(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*get_word(char const *s, char c, int *index)
{
	int		i;
	int		wdlen;
	char	*str;

	wdlen = 0;
	i = 0;
	while (s[(*index)] == c)
		(*index)++;
	i = *index;
	while (s[i] && s[i] != c)
	{
		wdlen++;
		i++;
	}
	str = my_alloc((wdlen + 1) * (sizeof(char)));
	if (!str)
		return (0);
	i = 0;
	while (s[(*index)] && s[(*index)] != c)
		str[i++] = s[(*index)++];
	str[i] = 0;
	return (str);
}

char	**ft_split(char *s, char c)
{
	int		c_occurence;
	int		i;
	char	**arr;
	int		index;

	if (s == NULL)
		return (0);
	index = 0;
	i = 0;
	c_occurence = c_count(s, c);
	arr = my_alloc(sizeof(char *) * (c_occurence + 1));
	if (!arr)
		return (0);
	while (i < c_occurence)
	{
		arr[i] = get_word(s, c, &index);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
