/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:01:07 by namichel          #+#    #+#             */
/*   Updated: 2025/02/24 00:30:14 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*MANDATORY PART*/
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *nptr);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strrchr(const char *string, int searchedChar);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
size_t	ft_strlen(const char *theString);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, char const *s2);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strdup(const char *source);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
void	*ft_memset(void *dest, int c, size_t count);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_isprint(int c);
int		ft_isdigit(int c);
int		ft_isascii(int c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	*ft_calloc(size_t elementCount, size_t elementSize);
int		ft_printf(const char *str, ...);
int		pf_hexa(unsigned int n, int c);
int		pf_hexa_p(unsigned long n);
int		len_nb(int nb);
char	*pf_itoa(int n);
char	*pf_itoa_u(unsigned int n);
void	*pf_memcpy(void *dst, const void *src, size_t n);
int		pf_putchar(char c);
void	pf_putchar_fd(char c, int fd);
int		pf_putpercent(void);
int		pf_putstr(char *s);
char	*pf_strchr(const char *s, int c);
char	*pf_strdup(const char *source);
int		pf_strlen(const char *str);
char	*pf_substr(char const *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
/*BONUS PART*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
