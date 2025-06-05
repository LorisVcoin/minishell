/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 23:43:10 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 19:17:19 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <fcntl.h>
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

	new = ft_calloc(sizeof(t_cmd) * 1, 1);
	if (!new)
		return (NULL);
	new->next = 0;
	new->cmd = 0;
	new->arg = 0;
	new->in.file = 0;
	new->in.flag = 0;
	new->in.eof = 0;
	new->in.fd = -2;
	new->out.fd = -2;
	new->out.eof = 0;
	new->out.flag = 0;
	new->out.file = 0;
	return (new);
}


//#TODO > ... > ... > -----> il faut peut-etre close les fds et > + (void) CARE
int	fill_infos(char **split, t_cmd *inputs, int *i)
{
	if (inputs->in.fd == -1 || inputs->out.fd == -1)
	{
		(*i)++;
		(*i)++;
		return (1);
	}
	if (split[*i] && ft_strcmp("<", split[*i]))
	{
		++(*i);
		inputs->in.file = verif_quote(ft_strdup(split[(*i)++]));
		inputs->in.flag = O_RDONLY;
		inputs->in.fd = open(inputs->in.file, inputs->in.flag);
		close(inputs->in.fd);
	}
	else if (split[*i] && ft_strcmp("<<", split[*i]))
	{
		++(*i);
		inputs->in.file = ft_strdup("/tmp/.minishell_heredoc");
		inputs->in.eof = verif_quote(ft_strdup(split[(*i)++]));
		heredoc(inputs->in.eof);
		inputs->in.flag = O_RDONLY;
		inputs->in.fd = open(inputs->in.file, inputs->in.flag);
		close(inputs->in.fd);
	}
	else if (split[*i] && split[*i + 1] && ft_strcmp(">", split[*i]))
	{
		++(*i);
		if (inputs->out.file)
			free_string(&(inputs->out.file));
		inputs->out.file = verif_quote(ft_strdup(split[(*i)++]));
		inputs->out.flag = O_CREAT | O_WRONLY | O_TRUNC;
		inputs->out.fd = open(inputs->out.file, inputs->out.flag, 0644);
		close(inputs->out.fd);
	}
	else if (split[*i] && ft_strcmp(">>", split[*i]))
	{
		++(*i);
		inputs->out.file = verif_quote(ft_strdup(split[(*i)++]));
		inputs->out.flag = O_CREAT | O_APPEND | O_WRONLY;
		inputs->out.fd = open(inputs->out.file, inputs->out.flag, 0644);
		close(inputs->out.fd);
	}
	else
		return (0);
	return (1);
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
	if (!result)
		return (0);
	result[i] = ft_strdup(new);
	if (!result[i])
	{
		free_tab(&result);
		return (0);
	}
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

/* Find the variable and return the expanded varariable.
 * RETURN VALUES :
 * 0 for ERROR.
 * A string containing the expanded variable. */
char	*my_getenv(char *s, char **envp)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = NULL;
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
			free_string(&cmd->cmd);
			cmd->cmd = path_cmd;
			break ;
		}
		free_string(&path_cmd);
	}
	free_tab(&all);
}

void	cmd_dup(char **split, char **envp, int *i, t_cmd *ptr)
{
	char	**tmp;

	tmp = 0;
	if (split[*i] && ptr->cmd == 0)
	{
		ptr->cmd = ft_strdup(split[*i]);
		if (access(ptr->cmd, X_OK) != 0)
			path(ptr, envp);
	}
	if (split[*i])
		tmp = concatanate(ptr->arg, split[(*i)++]);
	ptr->arg = tmp;
}

int	is_redirections(char *str)
{
	if (ft_strcmp(str, ">") || ft_strcmp(str, ">>") || ft_strcmp(str, "<") || ft_strcmp(str, "<<"))
		return (1);
	return (0);
}

int	set_cmd(t_inputs *inputs, char **split, char **envp)
{
	t_cmd	*ptr;
	int		i;

	i = 0;
	ptr = new_cmd();
	if (!ptr)
		return (0);
	inputs->cmds = ptr;
	while (split[i])
	{
		while (split[i] && split[i + 1] && (is_redirections(split[i])))
			fill_infos(split, ptr, &i);
		if (split[i] && ft_strcmp(split[i], "|") && ++i)
		{
			if (split[i] && split[i + 1] && (is_redirections(split[i])))
				continue ;
			if (!split[i])
			{
				ptr->arg = supre_quote(ptr->arg);
				if (!ptr->arg)
				{
					free_tab(&split);
					return (0);
				}
				ptr->arg = concatanate(ptr->arg, split[i - 1]);
			}
			else
			{
				// print_tab(ptr->arg);
				// ptr->arg = supre_quote(ptr->arg);
				// if (!ptr->arg)
				// {
					// free_tab(&split);
					// return (0);
				// }
				ptr->next = new_cmd();
				if (!next_cmd(&ptr))
					return (0);
			}
		}
		if (split[i])
		{
			split[i] = verif_quote(split[i]);
			if (!split[i])
			{
				free_tab(&split);
				return (0);
			}
			cmd_dup(split, envp, &i, ptr);
		}
	}
	free_tab(&split);
	return (0);
}
