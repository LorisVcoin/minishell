/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:36:05 by namichel          #+#    #+#             */
/*   Updated: 2025/05/27 19:45:01 by namichel         ###   ########.fr       */
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

int	env(char **envp)
{
	if (envp == 0)
		exit (EXIT_FAILURE);
	while (*envp)
	{
		if (where_is_equal(*envp))
			printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
