/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:30:06 by namichel          #+#    #+#             */
/*   Updated: 2025/03/05 02:06:47 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char *big, int index, char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (big[i + index] == little[i] && big[i + index] && (i + index) < len)
		i++;
	if (little[i])
		return (0);
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == 0)
		return ((char *)big);
	while (i < len && (unsigned char)big[i])
	{
		if (ft_search((char *)big, i, (char *)little, len))
			return ((char *)big + i);
		i++;
	}
	return (0);
}
