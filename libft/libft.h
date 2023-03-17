/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelbouha <oelbouha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:31:31 by oelbouha          #+#    #+#             */
/*   Updated: 2022/10/12 11:00:24 by oelbouha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

typedef struct s_split
{
	int		i;
	int		j;
	int		wordlen;
	char	next_stop_char;
	char	*next_stop;
	char	**str;
	char	*start;
}	t_split;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_tolower(int s);
int		ft_toupper(int s);
int		ft_isascii(int s);
int		ft_isalpha(int s);
int		ft_isalnum(int s);
int		ft_isdigit(int s);
int		ft_isprint(int s);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_atoi(char *str);
int		ft_lstsize(t_list *lst);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_itoa(int n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t	ft_strlcpy(char *dest, char *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, char *src, size_t size);
void	ft_striteri(char *s, void (*f)(unsigned int i, char *c));
void	ft_putstr_fd(char *str, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putendl_fd(char *str, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
void	*ft_calloc(size_t items, size_t size);
void	ft_bzero(void *b, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
char	*ft_search(const char *s, int c);
char	**split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);


#endif
