/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_hexa_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <namichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:09:26 by namichel          #+#    #+#             */
/*   Updated: 2024/11/13 21:01:20 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_hxd(int nbr)
{
	int	lower;

	lower = nbr + 87;
	write(1, &lower, 1);
}

static void	ft_putnbr_hxd(unsigned long n)
{
	int	nbr;
	int	ch;

	nbr = n % 16;
	ch = nbr + 48;
	if (n >= 16)
	{
		n = n / 16;
		if (n > 0)
			ft_putnbr_hxd(n);
	}
	if (nbr >= 10)
	{
		ft_write_hxd(nbr);
	}
	else
	{
		ch = nbr + 48;
		write(1, &ch, 1);
	}
	return ;
}

static int	ft_count(unsigned long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	return (count);
}

int	pf_hexa_p(unsigned long n)
{
	unsigned long	count;

	if (n == 0)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	write(1, "0x", 2);
	count = 2;
	count += ft_count(n);
	ft_putnbr_hxd(n);
	return (count);
}
