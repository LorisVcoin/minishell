/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 01:15:33 by namichel          #+#    #+#             */
/*   Updated: 2025/03/05 00:32:03 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

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

#endif
