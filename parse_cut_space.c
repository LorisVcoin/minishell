/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cut_space.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 03:03:44 by namichel          #+#    #+#             */
/*   Updated: 2025/05/24 11:20:25 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	temp_not_or_ok(char *line, char *pos)
{
	char	*first;
	char	*last;

	first = ft_strchr(line, '\'');
	if (first)
	{
		last = ft_strchr(first + 1, '\'');
		if (pos > first && pos < last)
			return (0);
	}
	first = ft_strchr(line, '\"');
	if (first)
	{
		last = ft_strchr(first + 1, '\"');
		if (pos > first && pos < last)
			return (0);
	}
	return (1);
}

/* Check if the pipe is surrounded by quotes.
 * 0 ERROR. 
 * 1 SUCCES.*/
int	ok_or_not(char *line, char *pos)
{
	char	*first;
	char	*first2;
	char	*last;

	first = ft_strchr(line, '\'');
	if (first)
	{
		if ((ft_strlen(first) - ft_strlen(line)) == 1)
			return (0);
		if (first)
		{
			last = ft_strchr(first + 1, '\'');
			if (!last && ft_strlen(first) == ft_strlen(line))
				return (1);
			if (!last)
				return (0);
			if (pos > first && pos < last)
				return (0);
		}
	}
	first2 = ft_strchr(line, '\"');
	if (first2)
	{
		if ((ft_strlen(first2) - ft_strlen(line)) == 1)
			return (0);
		if (first2)
		{
			last = ft_strchr(first2 + 1, '\"');
			if (!last)
				return (0);
			if (pos > first2 && pos < last)
				return (0);
		}
	}
	return (1);
}

/* This function checks if there is a pipe in the line. 
 * RETURN VALUE :
 * -1 ERROR the line start with '|'.
 *  0 if the pipe is surrounded by the character ' or " 
 *  i the size of space we need. */
static int	size(char *line)
{
	char	*buf;
	int		i;

	i = 0;
	buf = ft_strchr(line, '|');
	if (!buf)
		return (0);
	if (buf == line)
		return (-1);
	if ((*(buf - 1) == '\'' && *(buf + 1) == '\'')
		|| (*(buf - 1) == '\"' && *(buf + 1) == '\"'))
		return (0);
	while (buf)
	{
		buf = ft_strchr(buf + 1, '|');
		i += 2;
	}
	return (i);
}

/* Space the pipe if is possible.
 * RETURN VALUE :
 * NULL malloc failed.
 * line without spaces.
 * line with spaces.*/
char	*cut_space(char *line)
{
	int		i;
	int		pos;
	char	*str;

	if (size(line) <= 0)
		return (line);
	str = malloc(ft_strlen(line) + size(line) + 1);
	if (!str)
		return (NULL);
	i = -1;
	pos = -1;
	while (line[++pos] && ++i >= 0)
	{
		if (line[pos] == '|' && temp_not_or_ok(line, &line[pos]) == 1 && pos++)
		{
			str[i++] = ' ';
			str[i++] = '|';
			str[i++] = ' ';
		}
		str[i] = line[pos];
	}
	str[++i] = 0;
	free(line);
	line = str;
	return (line);
}
