/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:33:46 by namichel          #+#    #+#             */
/*   Updated: 2024/10/18 23:56:10 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = -1;
	if (size <= 0 || count <= 0)
		return (malloc(0));
	if ((count * size) / size != count)
		return (NULL);
	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	while (++i < count * size)
		ptr[i] = 0;
	return (ptr);
}
