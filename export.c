/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:52:11 by namichel          #+#    #+#             */
/*   Updated: 2025/05/28 20:40:27 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getpos(char *str, char c)
{
	int	pos;

	pos = ft_strchr(str, c) - str;
	if (pos == 0)
		return (ft_strlen(str));
	return (pos);
}

static int	get_idx(char *str, char **env)
{
	size_t	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(str, env[i], getpos(str, '=')))
			return (i);
	}
	return (-1);
}

static void	add_tab(char ***new_env, char *add, int *i, char **env)
{
	(*new_env)[*i] = ft_strdup(add);
	while ((*i)-- > 0)
		(*new_env)[*i] = env[*i];
}

static int	little_dupp_and_add(char ***new_env, char *add, int *i, char **env)
{
	(*new_env) = malloc(sizeof(char *) * ((*i) + 2));
	if (*new_env == 0)
		return (0);
	(*new_env)[(*i) + 1] = 0;
	(*new_env)[(*i)] = ft_strdup(add);
	if ((*new_env)[(*i)] == 0)
		return (0);
	while ((*i)-- > 0)
		(*new_env)[*i] = env[*i];
	return (1);
}

static int	dup_tab(char ***new_env, int *i, int pos, char **env)
{
	(*new_env) = malloc(sizeof(char *) * ((*i) + 1));
	if ((*new_env) == 0)
		return (0);
	(*new_env)[*i] = 0;
	while ((*i)-- > (pos +1))
		(*new_env)[*i] = env[*i];
	free(env[*i]);
	return (1);
}

char	**dupp_and_add(char **env, char *add, int pos)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		++i;
	if (pos == -1)
	{
		if (!little_dupp_and_add(&new_env, add, &i, env))
			return (0);
	}
	else
	{
		if (!dup_tab(&new_env, &i, pos, env))
			return (0);
		add_tab(&new_env, add, &i, env);
	}
	free(env);
	return (new_env);
}

void	exp_pwd(char ***envp, char *new_pwd)
{
	int	pos;

	pos = get_idx(new_pwd, *envp);
	if (pos != -1)
	{
		*envp = dupp_and_add(*envp, new_pwd, pos);
	}
}

int	export(t_cmd *command, char ***envp)
{
	int	i;
	int	pos;
	int	tmp;

	if (*envp == 0)
		return (EXIT_FAILURE);
	i = 0;
	while (command->arg[++i])
	{
		tmp = 0;
		while ((command->arg[i][tmp] && command->arg[i][tmp] != '=') || command->arg[i][0] == '=')
		{
			if (!env_name(command->arg[i][tmp]))
			{
				g_exit = 1;
				fprintf(stderr, "export: %s: not a valid identifier\n", command->arg[i]);
				return (EXIT_FAILURE);
			}
			tmp++;
		}
		pos = get_idx(command->arg[i], *envp);
		*envp = dupp_and_add(*envp, command->arg[i], pos);
	}
	return (EXIT_SUCCESS);
}
