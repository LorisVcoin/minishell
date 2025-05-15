/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varexp_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:20:49 by lviravon          #+#    #+#             */
/*   Updated: 2025/05/13 18:55:08 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/libft.h>

static int	get_len_var(char *line, int i)
{
	int	tmp;
	int	count_quote;

	count_quote = 0;
	tmp = i;
	while (line[tmp] && ft_isspace(line[tmp]) != 1)
	{
		if (line[tmp] == '"')
			count_quote++;
		tmp++;
	}
	return (tmp - i - count_quote);
}

static char	*expand_var(char *var, char **envp, int expand)
{
	int		i;
	int		j;
	char	*var_expend;

	i = 0;
	j = 0;
	while (envp[j] && expand != 1)
	{
		if (ft_strnstr(envp[j], var, ft_strlen(var)) != 0)
		{
			while (envp[j][i])
			{
				while (envp[j][i] != '=')
					i++;
				var_expend = ft_strdup(&envp[j][i + 1]);
				return (var_expend);
			}
		}
		j++;
	}
	return (var);
}

static	char	*new_line(char *var_expend, int len_var, char *line, int i)
{
	char	*tmp;
	int		j;
	int		x;
	int		y;

	x = 0;
	y = 0;
	j = 0;
	tmp = ft_strdup(line);
	free(line);
	line = ft_calloc(ft_strlen(tmp) + ft_strlen(var_expend) - len_var + 1, 1);
	if (!line)
		return (NULL);
	while (tmp[y])
	{
		if (x == i)
		{
			while (var_expend[j])
				line[x++] = var_expend[j++];
			y += len_var;
		}
		line[x++] = tmp[y++];
	}
	return (line);
}

static char	*get_var(char *line, char **envp, int i, int expand)
{
	char	*var;
	char	*var_expend;
	int		j;
	int		len_var;
	int		tmp;

	tmp = i;
	len_var = get_len_var(line, ++i) + 1;
	j = 0;
	var = ft_calloc(len_var, 1);
	while (i != len_var)
	{
		if (line[i] == '"')
		{
			while (i != len_var)
			{
				expand = 1;
				var[j++] = line[i++];
			}
		}
		var[j++] = line[i++];
	}
	var_expend = expand_var(var, envp, expand);
	line = new_line(var_expend, len_var, line, tmp);
	return (line);
}

char	*varexp_envp(char **envp, char *line)
{
	int		i;
	int		expand;
	int		tmp;

	expand = 0;
	i = 0;
	if (!*envp)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\'')
			while (line[i] != '\'')
				i++;
		if (line[i] == '$')
		{
			tmp = i;
			line = get_var(line, envp, tmp, expand);
		}
		i++;
	}
	return (line);
}
