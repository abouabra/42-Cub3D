/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:18:28 by abouabra          #+#    #+#             */
/*   Updated: 2022/12/04 17:29:47 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_dprintf(int fd, const char *str, ...);

void	ft_dputchar(char c, int *tracker, int fd);
void	ft_dputnbr(int n, int *tracker, int fd);
void	ft_dputstr(char *s, int *tracker, int fd);
void	ft_dput_unsigned_nbr(unsigned int nb, int *tracker, int fd);
void	ft_dput_hex_nbr(unsigned int nb, char x, int *tracker, int fd);
void	ft_dput_adress(void *ptr, int *tracker, int fd);

#endif
