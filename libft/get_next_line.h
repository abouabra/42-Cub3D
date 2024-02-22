/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:30:35 by abouabra          #+#    #+#             */
/*   Updated: 2022/11/13 15:24:54 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10000
# endif

char	*get_next_line(int fd);
char	*read_fd(int fd, char *line);
char	*set_the_line(char *line);
char	*set_next_line(char *line);

int		ft_strlen(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr(char *s, int c);

void	*my_alloc(size_t size);
void	garbage_collector(void *adress, int arg);
void	custom_exit(int exit_code);

#endif
