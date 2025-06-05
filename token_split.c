/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:20:21 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 18:09:34 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_token(t_token *t)
{
	t->len = 0;
	t->td = 0;
	t->tmp = 0;
	t->type = 0;
}

static char	*cpy_str(char *s, t_token *t, int *i)
{
	char	*res;
	int		next;

	res = malloc(t->len - t->td + 1);
	if (!res)
		return (0);
	res[t->len - t->td] = 0;
	next = 0;
	while (t->len-- - t->td)
	{
		if (s[*i + t->len - next] == '\"' && (t->type == 0 || t->type == 2))
			t->type = (t->type + 2) % 4;
		if (s[*i + t->len - next] == '\'' && (t->type == 0 || t->type == 1))
			t->type = (t->type + 1) % 2;
		res[t->len - t->td] = s[*i + t->len - next];
	}
	return (res);
}

static char	*split_str(char *s, int *i)
{
	t_token	t;
	char	*res;

	if (!s)
		return (0);
	init_token(&t);
	while (s[*i + t.len] && (s[*i + t.len] != ' ' || t.type))
	{
		if (s[*i + t.len] == '\"' && (t.type == 0 || t.type == 2))
			t.type = (t.type + 2) % 4;
		if (s[*i + t.len] == '\'' && (t.type == 0 || t.type == 1))
			t.type = (t.type + 1) % 2;
		t.len++;
	}
	t.tmp = t.len;
	res = cpy_str(s, &t, i);
	*i += t.tmp;
	return (res);
}

static int	count_helper(char *line, int *i)
{
	while (line[*i] && line[*i] == '\'' && line[++(*i)])
	{
		while (line[*i] != '\'')
		{
			if (line[*i] == '\0')
				return (-1);
			(*i)++;
		}
		(*i)++;
	}
	while (line[*i] && line[*i] == '\"' && line[++(*i)])
	{
		while (line[*i] != '\"')
		{
			if (line[*i] == '\0')
				return (-1);
			(*i)++;
		}
		(*i)++;
	}
	while (line[*i] && line[*i] != ' ' && line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	return (0);
}

static int	count(char *line)
{
	int	i;
	int	arg;

	i = 0;
	arg = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			if (line[i] == 0 && arg == 0)
				return (-1);
			if (line[i] == 0)
				return (arg);
		}
		if (count_helper(line, &i) == -1)
			return (-1);
		if (line[i] == '\'' || line[i] == '\"')
			arg--;
		arg++;
	}
	return (arg);
}

char	**token_split(char *line)
{
	char	**res;
	int		arg;
	int		i;
	int		tmp;

	arg = count(line);
	if (arg == -1)
		return (0);
	res = malloc(sizeof(char *) * (arg + 1));
	if (!res)
		return (0);
	res[arg] = 0;
	i = 0;
	tmp = arg;
	arg = 0;
	while (arg < tmp)
	{
		while (line[i] == ' ')
			i++;
		res[arg] = split_str(line, &i);
		arg++;
	}
	return (res);
}

/*
#define MAX_TOKEN 128
#define BUFFER_SIZE 4096

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

void	new_token(char **split, int j, char *buffer, int len)
{
	if (len > 0)
	{
		buffer[len] = '\0';
		split[j] = ft_strdup(buffer);
	}
}

char	**token_split(char *str)
{
	char	**split;
	int		i;
	int		j;
	char	buf[BUFFER_SIZE];
	char	quote;
	int		index_token;

	index_token = 0;
	quote = 0;
	i = 0;
	j = 0;
	split = (char **)malloc(sizeof(char *) * MAX_TOKEN);
	if (!split)
		return (NULL);
	while (str[i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
		{
			quote = str[i];
			buf[j++] = str[i];
		}
		else if (str[i] == quote)
		{
			quote = 0;
			buf[j++] = str[i];
		}
		else if (ft_isspace(str[i]) && quote == 0)
		{
			if (j > 0)
				new_token(split, index_token, buf, j);
			j = 0;
			index_token++;
		}
		else
			buf[j++] = str[i];
		i++;
	}
	if (j > 0)
	{
		new_token(split, index_token, buf, j);
		index_token++; // FIX il manquait le index TOKEN
	}
	split[index_token] = NULL;
	return (split);
}*/
