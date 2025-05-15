/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_gestion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:13:11 by lviravon          #+#    #+#             */
/*   Updated: 2025/04/17 20:36:55 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/libft.h>
#include <stdlib.h>

static int	space_count(char *line, int i, char c)
{
	int	space;

	space = 0;
	if (i != 0 && line[i - 1] != c && line[i - 1] != ' ')
		space++;
	if (line[i + 1] != c && line[i + 1] != ' ' && line[i + 1] != '\0')
		space++;
	return (space);
}

static char	*new_line(char *line, char *tmp, int i, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (tmp[y])
	{
		if (y == i)
		{
			if (i != 0 && tmp[y - 1] != c && tmp[y - 1] != ' ')
				line[x++] = ' ';
			line[x++] = tmp[y++];
			if (tmp[y] != c && tmp[y] != ' ')
				line[x++] = ' ';
		}
		line[x] = tmp[y];
		x++;
		y++;
	}
	return (line);
}

char	*space_redirec(char *line, int i, char c)
{
	char	*tmp;
	int		space;
	int		len;

	tmp = ft_strdup(line);
	len = ft_strlen(tmp);
	space = space_count(tmp, i, c);
	if (line[len - 1] == c || space == 0)
		return (line);
	free(line);
	line = calloc(len + space, 1);
	if (!line)
		return (NULL);
	line = new_line(line, tmp, i, c);
	return (line);
}
