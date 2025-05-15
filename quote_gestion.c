/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:41:08 by lviravon          #+#    #+#             */
/*   Updated: 2025/04/14 19:51:08 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_second_quote_place(char *line, int firPlace)
{
	int	i;

	i = firPlace + 1;
	while (line[i])
	{
		while (line [i] && line[i] != '"')
			i++;
		if (line[i] == '"')
			return (i);
		i++;
	}
	return (-1);
}

char	*supressed_double_quote(char *line, int firPlace, int secPlace)
{
	int		size;
	char	*tmp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	secPlace = get_second_quote_place(line, firPlace);
	if (secPlace == -1)
		return (NULL);
	tmp = ft_strdup(line);
	size = ft_strlen(line);
	free(line);
	line = calloc(size - 2 + 1, 1); // -2 quote + 1 '\0'
	while (tmp[x])
	{
		if (x == firPlace || x == secPlace)
			x++;
		line[y] = tmp[x];
		y++;
		x++;
	}
	return (line);
}
