/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:56:46 by namichel          #+#    #+#             */
/*   Updated: 2024/11/13 20:31:02 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_strdup(const char *source)
{
	char	*result;
	size_t	len;

	len = pf_strlen(source) + 1;
	result = malloc(len);
	if (!result)
		return (NULL);
	pf_memcpy(result, source, len);
	return (result);
}
