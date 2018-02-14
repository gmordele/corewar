/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmordele <gmordele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 18:32:05 by gmordele          #+#    #+#             */
/*   Updated: 2018/02/01 01:49:37 by gmordele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_pf.h"
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdarg.h>
# include <errno.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>

# ifdef linux
#  include <sys/types.h>
# endif

# define BUFF_SIZE_GNL	10000
# define FREE_GNL		(char **)1

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_lst
{
	char			*str;
	void			*ptr;
	int				i;
	long			l;
	struct s_lst	*prev;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_fd_buff
{
	int				fd;
	unsigned int	pos;
	ssize_t			n;
	char			*buff;
}					t_fd_buff;

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

int					ft_atoi_next(char **s);
long				ft_atol(const char *s);
char				*ft_capital(char *str);
int					ft_char(int value, int nb_char, ...);
void				ft_free(int nb_ptr, ...);
char				*ft_ftoa(long double ld);
int					ft_int(int nb_int, int value, ...);
int					ft_isspc(int c);
t_lst				*ft_l_add_bck(t_lst **list, t_lst *new);
t_lst				*ft_l_add_frt(t_lst **list, t_lst *new);
void				ft_l_del(t_lst **list);
t_lst				*ft_l_del_one(t_lst **list, t_lst *target);
t_lst				*ft_l_new(char *str, void *ptr, int i, long l);
void				*ft_malloc(int n);
long				ft_pow(long nb, int power);
void				*ft_ptr(void *address, int nb_ptr, ...);
char				*ft_round(char *s, int precision);
char				*ft_strjf(char *s1, char *s2, int nb_free);
char				*ft_strjf3(char *s1, char *s2, char *s3, int nbf);
char				*ft_strnewof(size_t size, char c);
char				*ft_utoa_base(unsigned long nb, int base, char *s);

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				**ft_strsplit(char const *s, char c);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *big, const char *little);
char				*ft_strnstr(const char *big, const char *little,
								size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_putnbr_base_fd(int n, int base, int fd);
void				ft_putnbr_base(int n, int base);
int					get_next_line(const int fd, char **line);
int					ft_atoi_base_fwd(char **nptr, int base);
int					ft_printf(const char *format, ...);
int					ft_atoi_base_fwd(char **nptr, int base);
int					ft_isspace(char c);
char				*skip_spaces(char *s);
char				*skip_word(char *s);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strjoinfree(char *s1, char *s2,
									int free_choice);
void				free_string_arr(char **arr);
int					ft_dprintf(int fd, const char *format, ...);
t_btree				*btree_create_node(void *item);
void				btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void				btree_apply_infix(t_btree *root, void (*applyf)(void *));
void				btree_apply_postfix(t_btree *root, void (*applyf)(void *));
void				btree_insert_data(t_btree **root, void *item,
									int (*cmpt)(void *, void *));
void				btree_free(t_btree **root, void (*del)(void *));
int					free_gnl_lst(t_list **lst);
#endif
