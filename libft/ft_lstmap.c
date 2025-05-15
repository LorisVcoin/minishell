/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 04:52:23 by namichel          #+#    #+#             */
/*   Updated: 2024/10/19 06:48:39 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_lstmapclear(t_list *result, void (*del)(void *), void *tmp)
{
	ft_lstclear(&result, del);
	del(tmp);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*result;
	void	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	result = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		new = ft_lstnew(tmp);
		if (!new)
		{
			ft_lstmapclear(result, del, tmp);
			return (NULL);
		}
		ft_lstadd_back(&result, new);
		lst = lst->next;
	}
	return (result);
}
