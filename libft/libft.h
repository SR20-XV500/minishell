/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlassere <tlassere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:54:21 by tlassere          #+#    #+#             */
/*   Updated: 2023/10/21 12:06:17 by tlassere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "./get_next_line.h"
# include "./ft_printf/headers/ft_printf.h"

# define MEMORY_SET_BECAUSE_NO_MEMORY_FRESH 69
# define MALLOC_FAIL -12
# define BAD_PARAMETER 3
# define OVERFLOW 4
# define SUCCESS 0
# define FAIL 1
# define CMP_EGAL 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef unsigned long long	t_bt8;

void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);

void		ft_putnbr_fd(int n, int fd);
void		ft_putendl_fd(char *s, int fd);
ssize_t		ft_putchar_fd(char c, int fd);
ssize_t		ft_putstr_fd(char *s, int fd);

void		ft_striteri(char *s, void (*f)(unsigned int, char *));

void		*ft_calloc(size_t nmemb, size_t size);

char		*ft_strdup(const char *s);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strrev(char *s);

char		*ft_itoa(int n);
char		*ft_int_convert_base(int dec, char *base);
char		*ft_uint_convert_base(unsigned int dec, char *base);
char		*ft_bt8_convert_base(t_bt8 dec, char *base);
int			ft_atoi(const char *nptr);
long long	ft_atoll(const char *nptr);
int			ft_check_overflow(const char *str, long long nbr);

int			ft_abs(int val);

size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);

void		ft_tab_free(char **tabs);
int			ft_tab_len(char **tab);
char		**ft_tab_dump(char **tab);
char		**ft_tab_join(char **tab, const char *el);
char		**ft_tab_dump_join(char *const *tab, const char *el);
char		**ft_tab_del(char **tab, int index);
char		**ft_split(char const *s, char c);

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_isascii(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isprint(int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp_s2(const char *s1, const char *s2);

void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
