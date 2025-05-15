/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <namichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:43:13 by namichel          #+#    #+#             */
/*   Updated: 2024/11/13 21:12:13 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_do_xpu(const char *str, ...)
{
	int		count;
	char	*substr;
	char	*s1;
	va_list	args;

	va_start(args, str);
	s1 = pf_strchr(str, '%');
	count = 0;
	if (s1[1] == 'x')
		count += pf_hexa(va_arg(args, unsigned int), 'x');
	else if (s1[1] == 'X')
		count += pf_hexa(va_arg(args, unsigned int), 'X');
	else if (s1[1] == 'p')
		count += pf_hexa_p(va_arg(args, unsigned long));
	else if (s1[1] == 'u')
	{
		substr = pf_itoa_u((unsigned int)va_arg(args, unsigned int));
		count += pf_putstr(substr);
		free (substr);
	}
	va_end(args);
	return (count);
}

static int	ft_do_csid(const char *str, ...)
{
	int		count;
	char	*substr;
	char	*s1;
	va_list	args;

	va_start(args, str);
	s1 = pf_strchr(str, '%');
	count = 0;
	if (s1[1] == 'c')
	{
		pf_putchar_fd(va_arg(args, int), 1);
		count++;
	}
	else if (s1[1] == 's')
		count = count + pf_putstr(va_arg(args, char *));
	else if (s1[1] == 'i' || s1[1] == 'd')
	{
		substr = pf_itoa(va_arg(args, int));
		count += pf_putstr(substr);
		free(substr);
	}
	va_end(args);
	return (count);
}

static int	ft_helper(const char *str, char *s1)
{
	int		count;
	char	*substr;

	count = 0;
	substr = pf_substr(str, 0, (s1 - str));
	count = count + pf_putstr(substr);
	free (substr);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	char	*s1;
	int		count;

	if (!str)
		return (0);
	s1 = (char *)str;
	count = 0;
	va_start(args, str);
	while (str && s1)
	{
		s1 = pf_strchr(str, '%');
		if (s1 == NULL)
			return (count += pf_putstr((char *)str));
		else
			count += ft_helper(str, s1);
		if (s1[1] == 'c' || s1[1] == 's' || s1[1] == 'd' || s1[1] == 'i')
			count += ft_do_csid(s1, va_arg(args, void *));
		else if (s1[1] == 'p' || s1[1] == 'u' || s1[1] == 'x' || s1[1] == 'X')
			count += ft_do_xpu(s1, va_arg(args, void *));
		else if (s1[1] == '%')
			count += pf_putpercent();
		str = s1 + 2;
	}
	return (count);
}
