/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:52:46 by namichel          #+#    #+#             */
/*   Updated: 2024/10/19 01:28:11 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, char const *s2)
{
	int		i;
	int		a;
	int		b;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	i = -1;
	ptr = malloc(sizeof(char) * (a + b + 1));
	if (!ptr)
		return (NULL);
	while (++i < a)
		ptr[i] = s1[i];
	i--;
	while (++i - a < b)
		ptr[i] = s2[i - a];
	ptr[i] = '\0';
	return (ptr);
}
