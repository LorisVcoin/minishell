/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 04:28:33 by namichel          #+#    #+#             */
/*   Updated: 2024/10/15 04:31:48 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		index;
	t_list	*elem;

	index = 0;
	if (lst == NULL)
		return (index);
	elem = lst;
	while (elem != NULL)
	{
		elem = elem->next;
		index++;
	}
	return (index);
}
