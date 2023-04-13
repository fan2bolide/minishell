/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:56:05 by bajeanno          #+#    #+#             */
/*   Updated: 2023/04/12 06:13:01 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <limits.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			ft_putchar(int c);
int			ft_isset(char c, char const *set);

char		*ft_strcat(char *src, char *dest);
char		*ft_strncat(char *s1, const char *s2, int n);
size_t		ft_strlcat(char *dest, const char *src, size_t dstsize);

size_t		ft_strlen(const char *s);

void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

int			ft_atoi(const char *str);
long long	ft_atoll(const char *str);
char		*ft_itoa(int n);

char		*ft_strmap(char const *s, char (*f)(char));
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);

char		*ft_strrchr(const char *s, int c);
char		*ft_strchr(const char *s, int c);

char		*ft_strncpy(char *str, char *dest, int n);
char		*ft_strcpy(char *src, char *dest);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);

int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strnjoin(char *s1, const char *s2, int n);
char		*ft_strjoin_free_s1(char *s1, char *s2);
char		*ft_strnjoin_free_s1(char *s1, char *s2, int n);
char		*ft_strjoin_secure(char const *s1, char const *s2);
char		**ft_split(const char *s, char c);
void		ft_split_destroy(char **split);
char		**ft_old_split(const char *s, char c);
void		ft_old_split_destroy(char **split);

int			ft_putstr(char const *s);
size_t		ft_putendl(char const *s);

char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
char		*ft_strdup(char *str);
char		*ft_strndup(char *str, size_t n);
void		ft_strclr(char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strtrim(char const *s, char const *set);

void		*ft_calloc(size_t count, size_t size);
void		*ft_realloc(void *data, size_t size, size_t new_size);
void		*ft_memalloc(size_t size);
void		*ft_memset(void *pointer, int value, size_t count);
void		ft_memdel(void **ap);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int nb, int fd);
int			ft_putnbr(int nb);

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstpop_back(t_list **list, void (*del)(void *));
void		ft_lstpop_front(t_list **list, void (*del)(void *));
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstclear_mais_pas_trop(t_list **lst); //ne passe pas la norme
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

char		*get_next_line(int fd);
int			ft_printf(const char *format, ...);

int			ft_max(int a, int b);
int			ft_min(int a, int b);

size_t		ft_arrsize(void **arr);
void		**ft_dup_arr(void **arr, size_t sizeof_arr_elemnt);
void		cpy_arr(void **arr_src, void **arr_dest);
void		**ft_lst_to_arr(t_list *lst, size_t size_of_arr_elemnt);

size_t		count_strs(const char *s, char c);
int			str_starts_with(char *str, char *keyword);
bool		str_contains_digits_only(char *str);
bool		can_be_converted_to_long(char *argv1);
void		ft_free_arr(void **array, void (*del)(void *));

#endif