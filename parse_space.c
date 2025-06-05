/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 05:00:31 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 19:01:18 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	loop(char *line, int *i, int *n, char c)
{
	int	check;

	check = 0;
	if (*i > 0 && line[*i - 1] != ' ')
		++(*n);
	while (line[*i] && line[*i] == c)
	{
		if (line[*i + 1] == 0)
			return (-1);
		(*i)++;
		(*n)++;
		check++;
		if (check == 3)
			return (-1);
		if (line[*i] && line[*i] != ' ' && line[*i] != c)
			(*n)++;
	}
	return (0);
}

static int	count(char *line)
{
	int	i;
	int	n;
	int	quote;

	quote = 0;
	i = 0;
	n = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quote != 2)
			quote = (quote + 1) % 2;
		if (line[i] == '\'' && quote != 1)
			quote = (quote + 2) % 4;
		if (line[i] == '<' && quote == 0)
			if (loop(line, &i, &n, '<'))
				return (-1);
		if (line[i] == '>' && quote == 0)
			if (loop(line, &i, &n, '>'))
				return (-1);
		i++;
		n++;
	}
	return (n);
}

static int	proxy(char *sign)
{
	if (*(sign) != '\'' && *(sign + 2) != '\'')
		if (*(sign) != '\"' && *(sign + 2) != '\"')
			return (1);
	return (0);
}

static void	putstr(char *res, char *line, int i, int x)
{
	char	*tmp;
	char	*tmp_tmp;

	tmp = ft_strdup(line);
	tmp_tmp = tmp;
	while (line[++i])
	{
		res[i + x] = line[i];
		if (ok_or_not(tmp, &line[i]) == 1)
		{
			if (line[i] != '>' && line[i] != '<' && line[i] != ' ' && line[i
				+ 1] && line[i + 2] && (line[i + 1] == '>' || line[i
					+ 1] == '<') && proxy(&line[i]))
				res[i + ++x] = ' ';
			if (line[i] == '<' && line[i + 1] && line[i + 1] != '<' && line[i
				+ 1] != ' ')
				res[i + ++x] = ' ';
			if (line[i] == '>' && line[i + 1] && line[i + 1] != '>' && line[i
				+ 1] != '\'')
				res[i + ++x] = ' ';
		}
		if (tmp)
			tmp++;
	}
	free_string(&tmp_tmp);
}
/*
static void	putstr(char *res, char *line)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (line[i])
	{
		res[i + x] = line[i];
		if (ok_or_not(line, &line[i]) == 1)
		{
			if (line[i] != '>' && line[i] != '<' && line[i] != ' ' && line[i
				+ 1] && ((line[i + 1] == '>' || line[i + 1] == '<')
					&& proxy(&line[i])))
				res[i + ++x] = ' ';
			if (line[i] == '<' && line[i + 1] && line[i + 1] != '<' && line[i
				+ 1] != ' ')
				res[i + ++x] = ' ';
			if (line[i] == '>' && line[i + 1] && line[i + 1] != '>' && line[i
				+ 1] != ' ')
				res[i + ++x] = ' ';
		}
		i++;
	}
}
*/

int	char_redirections(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

char	*split_on_redirection(char *str)
{
	int		i;
	int		y;
	char	*res;

	y = 0;
	i = 0;
	res = ft_calloc(sizeof(char) * ft_strlen(str) * 2, 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			res[y++] = str[i++];
			while (str[i] && str[i] != '\'')
				res[y++] = str[i++];
			res[y++] = str[i++];
			continue ;
		}
		if (str[i] == '\"')
		{
			res[y++] = str[i++];
			while (str[i] && str[i] != '\"')
				res[y++] = str[i++];
			res[y++] = str[i++];
			continue ;
		}
		if (char_redirections(str[i]) && str[i + 1] && !char_redirections(str[i + 1]) && !char_redirections(str[i - 1]))
		{
			res[y++] = ' ';
			res[y++] = str[i++];
			continue ;
		}
		res[y++] = str[i++];
	}
	free_string(&str);
	return (res);
}

char	*space(char *line)
{
	int		n;
	char	*res;

	n = count(line);
	if (n == -1)
	{
		free(line);
		return (NULL);
	}
	res = ft_calloc(sizeof(char) * (n * 2 + 1), 1);
	if (!res)
	{
		free(line);
		return (0);
	}
	res[n] = '\0';
	putstr(res, line, -1, 0);
	// printf("%s\n", res);
	res = split_on_redirection(res);
	free(line);
	return (res);
}
