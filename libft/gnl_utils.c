/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 16:58:22 by abouabra          #+#    #+#             */
/*   Updated: 2022/11/13 14:31:02 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1)
	{
		s1 = my_alloc(1 * sizeof(char));
		if (!s1)
			return (0);
		s1[0] = 0;
	}
	if (s2 == NULL)
		return (0);
	str = my_alloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	i = -1;
	j = 0;
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*set_the_line(char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (!line[0])
		return (0);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	str = my_alloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		str[i++] = '\n';
	str[i] = 0;
	return (str);
}

char	*set_next_line(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (0);
	str = my_alloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!str)
		return (0);
	i++;
	while (line[i])
		str[j++] = line[i++];
	str[j] = 0;
	return (str);
}
