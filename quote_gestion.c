/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:41:08 by lviravon          #+#    #+#             */
/*   Updated: 2025/05/15 22:29:50 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/libft.h>

static int	get_second_quote_place(char *line, int firPlace, int c)
{
	int	i;

	i = firPlace + 1;
	while (line[i])
	{
		while (line [i] && line[i] != c)
			i++;
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static char	*supressed_(char *line, int firPlace, int secPlace)
{
	char	*line2;
	int		x;
	int		y;
	int		c;

	c = line[firPlace];
	x = 0;
	y = 0;
	secPlace = get_second_quote_place(line, firPlace, c);
	secPlace = ft_strlen(line) - 1;
	if (secPlace == -1)
		return (NULL);
	line2 = calloc(ft_strlen(line) - 2 + 1, 1);
	while (line[x])
	{
		if (x == firPlace || x == secPlace)
			x++;
		line2[y] = line[x];
		y++;
		x++;
	}
	return (line2);
}

char	**supressed_double_quote(char **strs)
{
	char	**strs2;
	int		i;
	int		j;

	j = 0;
	while (strs[j])
		j++;
	strs2 = malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (strs[j])
	{
		if (strs[j][i] == '\'' || strs[j][i] == '"')
			strs2[j] = supressed_(strs[j], i, 0);
		else
			strs2[j] = ft_strdup(strs[j]);
		j++;
	}
	free_2d(strs);
	return (strs2);
}
