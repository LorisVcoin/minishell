/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:02:27 by namichel          #+#    #+#             */
/*   Updated: 2025/05/24 11:19:47 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dup_env(char **envp)
{
	int		i;
	char	**result;

	i = 0;
	while (envp[i])
		i++;
	result = malloc(sizeof(char *) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		result[i] = ft_strdup(envp[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}
