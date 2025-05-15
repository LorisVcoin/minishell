/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:56:46 by namichel          #+#    #+#             */
/*   Updated: 2024/10/19 04:53:44 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	char	*result;
	size_t	len;

	len = ft_strlen(source) + 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	ft_memcpy(result, source, len);
	return (result);
}
