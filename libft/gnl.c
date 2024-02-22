/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:37:28 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/19 15:04:19 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *line)
{
	char	*str;
	int		counter;

	str = my_alloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (0);
	counter = 1;
	while (!ft_strchr(line, '\n') && counter != 0)
	{
		counter = read(fd, str, BUFFER_SIZE);
		if (counter == -1)
			return (0);
		str[counter] = '\0';
		line = ft_strjoin_gnl(line, str);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line[OPEN_MAX];
	char		*final;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	line[fd] = read_fd(fd, line[fd]);
	if (!line[fd])
		return (0);
	final = set_the_line(line[fd]);
	line[fd] = set_next_line(line[fd]);
	return (final);
}
