/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:38:10 by abouabra          #+#    #+#             */
/*   Updated: 2023/09/28 17:31:48 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_charset(char str, char *charset)
{
	while (*charset)
	{
		if (str == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	split_charset_word_count(char const *str, char *charset)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (ft_is_charset(str[i], charset))
			i++;
		else
		{
			count++;
			while (str[i] && !ft_is_charset(str[i], charset))
				i++;
		}
	}
	return (count);
}

static char	*get_word(char const *s, char *charset, int *index)
{
	int		i;
	int		wdlen;
	char	*str;

	wdlen = 0;
	i = 0;
	while (s[(*index)] && ft_is_charset(s[(*index)], charset))
		(*index)++;
	i = *index;
	while (s[i] && !ft_is_charset(s[i], charset))
	{
		wdlen++;
		i++;
	}
	str = my_alloc((wdlen + 1) * (sizeof(char)));
	if (!str)
		return (0);
	i = 0;
	while (s[(*index)] && !ft_is_charset(s[(*index)], charset))
		str[i++] = s[(*index)++];
	str[i] = 0;
	return (str);
}

char	**ft_split_charset(char *s, char *charset)
{
	int		c_occurence;
	int		i;
	char	**arr;
	int		index;

	if (s == NULL)
		return (0);
	index = 0;
	i = 0;
	c_occurence = split_charset_word_count(s, charset);
	arr = my_alloc(sizeof(char *) * (c_occurence + 1));
	if (!arr)
		return (0);
	while (i < c_occurence)
	{
		arr[i] = get_word(s, charset, &index);
		i++;
	}
	arr[i] = 0;
	return (arr);
}
