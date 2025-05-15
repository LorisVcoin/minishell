/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:43:10 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 05:49:49 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <fcntl.h>
#include <libft/libft.h>
#include <stddef.h>
#include <unistd.h>

int	ft_strcmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == 0 && *s2 == 0)
		return (1);
	return (0);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	// TODO change to CALLOC (ET enleve tout ;les )000
	new->next = 0;
	new->cmd = 0;
	new->arg = 0;
	new->in.file = 0;
	new->in.flag = 0;
	new->in.eof = 0;
	new->out.eof = 0;
	new->out.flag = 0;
	new->out.file = 0;
	return (new);
}

void	fill_infos(char **split, t_cmd *inputs, int *i)
{
	if (split[*i] && ft_strcmp("<", split[*i]) && ++(*i))
	{
		inputs->in.file = ft_strdup(split[(*i)++]);
		inputs->in.flag = O_RDONLY;
	}
	if (split[*i] && ft_strcmp("<<", split[*i]) && ++(*i))
	{
		inputs->in.file = ft_strdup(".here_doc");
		inputs->in.eof = ft_strdup(split[(*i)++]);
		inputs->in.flag = O_RDONLY;
	}
	if (split[*i] && ft_strcmp(">", split[*i]) && ++(*i))
	{
		inputs->out.file = ft_strdup(split[(*i)++]);
		inputs->out.flag = O_CREAT | O_RDWR | O_TRUNC;
	}
	if (split[*i] && ft_strcmp(">>", split[*i]) && ++(*i))
	{
		inputs->out.file = ft_strdup(split[(*i)++]);
		inputs->out.flag = O_CREAT | O_APPEND | O_WRONLY;
	}
}

int	next_cmd(t_cmd **ptr)
{
	if ((*ptr)->next == 0)
		return (0);
	*ptr = (*ptr)->next;
	return (1);
}

char	**concatanate(char **args, char *new)
{
	int		i;
	char	**result;

	i = 0;
	if (args)
	{
		while (args[i])
			i++;
	}
	result = malloc(sizeof(char *) * (i + 2));
	result[i] = ft_strdup(new);
	result[i + 1] = NULL;
	while (i--)
		result[i] = args[i];
	free(args);
	return (result);
}

char	*expend_equal(char *s)
{
	size_t	len;
	char	*add_eq;

	len = ft_strlen(s);
	add_eq = malloc(len + 2);
	if (!add_eq)
		return (0);
	ft_memcpy(add_eq, s, len);
	add_eq[len] = '=';
	add_eq[len + 1] = 0;
	return (add_eq);
}

char	*my_getenv(char *s, char **envp)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	new_str = expend_equal(s);
	if (!new_str)
		return (0);
	while (envp[i])
	{
		if (ft_strncmp(new_str, envp[i], ft_strlen(new_str)) == 0)
			break ;
		i++;
	}
	if (envp[i] == 0)
	{
		free(new_str);
		return (0);
	}
	j = 0;
	while (s[j])
		j++;
	free(new_str);
	return (&(envp[i][j + 1]));
}

char	*path_conca(char *s1, char *s2)
{
	char	*result;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	i = 0;
	while (s2[i])
		i++;
	len += i + 1;
	result = malloc(len + 1);
	if (result == 0)
		return (0);
	result[0] = 0;
	len = 0;
	i = 0;
	while (s1[i])
		result[len++] = s1[i++];
	result[len++] = '/';
	i = 0;
	while (s2[i])
		result[len++] = s2[i++];
	result[len] = '\0';
	return (result);
}

void	path(t_cmd *cmd, char **envp)
{
	int		i;
	char	*path_cmd;
	char	*path;
	char	**all;

	path = my_getenv("PATH", envp);
	if (path == 0)
		return ;
	all = ft_split(path, ':');
	if (all == 0)
		return ;
	i = 0;
	while (all[i])
	{
		path_cmd = path_conca(all[i++], cmd->cmd);
		if (access(path_cmd, X_OK) == 0)
		{
			free_string(&cmd->cmd); //#TODO
			cmd->cmd = path_cmd;
			break ;
		}
		free_string(&path_cmd);
	}
	free_tab(&all);
}

void	cmd_dup(char **split, char **envp, int *i, t_cmd *ptr)
{
	if (split[*i] && ptr->cmd == 0)
	{
		ptr->cmd = ft_strdup(split[*i]);
		if (access(ptr->cmd, X_OK) != 0)
			path(ptr, envp);
	}
	if (split[*i])
		ptr->arg = concatanate(ptr->arg, split[(*i)++]);
}

void	set_cmd(t_inputs *inputs, char **split, char **envp)
{
	t_cmd	*ptr;
	int		i;

	i = 0;
	ptr = new_cmd();
	if (!ptr)
		return ;
	inputs->cmds = ptr;
	while (split[i])
	{
		fill_infos(split, ptr, &i);
		if (split[i] && ft_strcmp(split[i], "|") && ++i)
		{
			if (!split[i])
				ptr->arg = concatanate(ptr->arg, split[i - 1]);
			else
			{
				ptr->next = new_cmd();
				if (!next_cmd(&ptr))
					return ;
			}
		}
		cmd_dup(split, envp, &i, ptr);
	}
	free_tab(&split);
}
