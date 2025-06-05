/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 02:44:54 by namichel          #+#    #+#             */
/*   Updated: 2025/05/24 11:20:08 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

static int	heredoc_cmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == '\n' && *s2 == 0)
		return (1);
	return (0);
}

static void	print(char *line, int fd)
{
	if (line == 0)
		return ;
	while (*line)
	{
		write(fd, line, 1);
		line++;
	}
}

void	heredoc(char *eof)
{
	char	*line;
	int		fd_here;

	line = 0;
	fd_here = open("/tmp/.minishell_heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (heredoc_cmp(line, eof) == 0)
	{
		print(line, fd_here);
		free_string(&line);
		write(1, ">>> ", 4);
		line = get_next_line(0);
	}
	free_string(&line);
	close(fd_here);
}
