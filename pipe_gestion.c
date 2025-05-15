/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 19:13:11 by lviravon          #+#    #+#             */
/*   Updated: 2025/04/17 15:38:41 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_number_of_space(char *line, int i)
{
	int		space;

	space = 0;
	if (ft_isspace(line[i - 1]) != 1 && ft_isspace(line[i + 1]) != 1)
		space = 2;
	if ((ft_isspace(line[i - 1]) == 1 && ft_isspace(line[i + 1]) != 1)
		|| (ft_isspace(line[i + 1]) == 1 && ft_isspace(line[i - 1]) != 1))
		space = 1;
	return (space);
}

static char	*add_space(char *line, int i, char *tmp)
{
	int	add;

	add = 0;
	if (tmp[i - 1] != ' ')
	{
		line[i + add] = ' ';
		add++;
	}
	line[i + add] = '|';
	if (tmp[i + 1] != ' ')
	{
		add++;
		line[i + add] = ' ';
	}
	return (line);
}

static char	*_spacestr(char *tmp, char *line, int _posChar)
{
	int	add;
	int	i;
	int	space;

	i = 0;
	add = 0;
	space = set_number_of_space(tmp, _posChar);
	while (tmp[i])
	{
		if (i == _posChar && space != 0)
		{
			add_space(line, i, tmp);
			if (tmp[i - 1] != ' ' || tmp[i + 1] != ' ')
			{
				add++;
				i++;
				if (space == 2)
					add = 2;
				space = 0;
			}
		}
		line[i + add] = tmp[i];
		i++;
	}
	return (line);
}

char	*space_pipe(char *line, int i)
{
	char	*tmp;
	int		len;
	int		space;

	len = ft_strlen(line);
	if ((i == 0 || len - 1 == i) && line[i] == '|')
		return (line);
	space = set_number_of_space(line, i);
	if (space == 0)
		return (line);
	len += space;
	tmp = ft_strdup(line);
	free(line);
	line = ft_calloc(len + 1, 1);
	if (!line)
		return (NULL);
	if (space != 0)
		line = _spacestr(tmp, line, i);
	return (line);
}
