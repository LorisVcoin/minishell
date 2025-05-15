/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:36:05 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 07:42:33 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	where_is_equal(char *envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i] == '=')
			return (1);
	}
	return (0);
}

void	env(char **envp)
{
	if (envp == 0)
		return ;
	while (*envp)
	{
		if (where_is_equal(*envp))
			printf(YELLOW "%s\n" RESET, *envp);
		envp++;
	}
}
