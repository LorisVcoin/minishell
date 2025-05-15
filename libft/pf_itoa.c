/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:19:43 by namichel          #+#    #+#             */
/*   Updated: 2024/11/13 20:30:02 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_nb(int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len ++;
		nb *= -1;
	}
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*pf_itoa(int n)
{
	int		i;
	long	nb;
	char	*result;

	nb = n;
	i = len_nb(nb);
	result = (char *)malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[i--] = '\0';
	if (nb < 0)
		nb *= -1;
	while (i >= 0)
	{
		result[i--] = (nb % 10) + 48;
		nb = nb / 10;
	}
	nb = n;
	if (nb < 0)
		result[0] = '-';
	return (result);
}
