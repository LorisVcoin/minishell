/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:21:30 by namichel          #+#    #+#             */
/*   Updated: 2024/10/19 05:33:59 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_s;
	char	*str;

	i = 0;
	len_s = ft_strlen(s);
	if (len >= len_s - start)
		len = len_s - start;
	if (start >= len_s)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (start < len_s && i < len)
		str[i++] = (char)s[start++];
	str[i] = '\0';
	return (str);
}
