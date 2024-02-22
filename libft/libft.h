/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra <abouabra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:29:23 by abouabra          #+#    #+#             */
/*   Updated: 2023/09/28 17:32:45 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
// GET NEXT LINE
# include "get_next_line.h"

// PRINTF
# include "ft_dprintf.h"

//part 1
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_strlen(char *s);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, void *src, size_t n);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(char *str, int c);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_memchr(void *s, int c, size_t n);
int					ft_memcmp(void *s1, void *s2, size_t n);
char				*ft_strnstr(char *big, char *little, size_t len);
int					ft_atoi(char *str);
void				*ft_calloc(size_t nitems, size_t size);
char				*ft_strdup(char *s1);
void				*ft_memmove(void *dst, void *src, size_t len);
size_t				ft_strlcpy(char *dst, char *src, size_t size);
size_t				ft_strlcat(char *dst, char *src, size_t size);

//part 2
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_itoa(int n);
char				**ft_split(char *s, char c);

//Bonus part
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new_node);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new_node);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

void				*my_alloc(size_t size);
void				garbage_collector(void *adress, int arg);
void				custom_exit(int exit_code);

char				**ft_split_charset(char *s, char *charset);

#endif
