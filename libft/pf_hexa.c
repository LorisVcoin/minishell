/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <namichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:00:52 by namichel          #+#    #+#             */
/*   Updated: 2024/11/13 21:14:12 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write_hexa(int nbr, int c)
{
	int	upper;
	int	lower;

	upper = nbr + 55;
	lower = nbr + 87;
	if (c == 'x')
		write(1, &lower, 1);
	else if (c == 'X')
		write(1, &upper, 1);
}

static void	ft_putnbr_hexa(unsigned int n, int c)
{
	int	nbr;
	int	ch;

	nbr = n % 16;
	ch = nbr + 48;
	if (n >= 16)
	{
		n = n / 16;
		if (n > 0)
			ft_putnbr_hexa(n, c);
	}
	if (nbr >= 10 && (c == 'x' || c == 'X'))
		ft_write_hexa(nbr, c);
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

int	pf_hexa(unsigned int n, int c)
{
	unsigned long	count;

	count = 0;
	count += ft_count(n);
	ft_putnbr_hexa(n, c);
	return (count);
}
