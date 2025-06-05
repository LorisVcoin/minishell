/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:49:14 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 16:28:53 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	getpos(char *str, char c)
{
	return (ft_strchr(str, c) - str);
}

static int	get_idx(char *str, char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str))
			&& getpos(env[i], '=') == ft_strlen(str))
			return (i);
	}
	return (-1);
}

size_t	count_bytes(char **env, int pos)
{
	size_t	result;
	int		i;

	i = -1;
	result = 0;
	while (++i != pos && env[i])
		result += sizeof(env[i]);
	return (result);
}
/*
char	**unset_env(char **env, size_t pos)
{
	size_t	len;
	char	**new_env;

	len = 0;
	while (env[len])
		++len;
	new_env = malloc(sizeof(char *) * (len + 1));
	new_env[len] = NULL;
	ft_memcpy(new_env, env, count_bytes(env, pos));
	ft_memcpy(new_env + pos, env + pos, count_bytes(env + pos, -1));
	free(*(env + pos));
	free(env);
	return (new_env);
}
*/

char	**unset_env(char **env, size_t pos)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	**new_env;

	len = 0;
	while (env[len])
		++len;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (i == pos)
		{
			++i;
			continue ;
		}
		new_env[j] = ft_strdup(env[i]);
		if (!new_env[j])
		{
			free_tab(&new_env);
			return (NULL);
		}
		++j;
		++i;
	}
	new_env[j] = NULL;
	free_tab(&env);
	return (new_env);
}

int	unset(t_cmd *command, char ***envp)
{
	int	i;
	int	pos;

	if (!envp[0])
		return (EXIT_FAILURE);
	i = 0;
	while (command->arg[++i])
	{
		pos = get_idx(command->arg[i], *envp);
		if (pos != -1)
			*envp = unset_env(*envp, pos);
	}
	return (EXIT_SUCCESS);
}
