/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 07:20:21 by namichel          #+#    #+#             */
/*   Updated: 2025/05/15 19:41:49 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/libft.h>

// #define MAX_TOKEN 128
// #define BUFFER_SIZE 4096

static unsigned int	count_token(char *s)
{
	unsigned int	i;
	unsigned int	count_str;
	unsigned int	j;

	i = 0;
	j = 0;
	count_str = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]) && s[i + 1] != '\0' && ft_isspace(s[i + 1]) != 1)
			count_str++;
		i++;
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[j]))
			j++;
		i++;
	}
	if (i == j)
		return (0);
	return (count_str + 1);
}

void	new_token(char **split, int j, char *buffer, int len)
{
	if (len > 0)
	{
		buffer[len] = '\0';
		split[j] = ft_strdup(buffer);
	}
}

static t_splitter	init_s(char *str)
{
	t_splitter	init;
	int			size_strs;
	int			buffer_size;

	buffer_size = ft_strlen(str);
	size_strs = count_token(str);
	init.split = (char **)malloc(sizeof(char *) * size_strs + 1);
	init.i = 0;
	init.j = 0;
	init.buffer = malloc(sizeof(char) * buffer_size);
	init.quote = 0;
	init.token_index = 0;
	return (init);
}

static t_splitter	splitting(t_splitter split, char *str)
{
	if (str[split.i] == '\'' || str[split.i] == '"')
	{
		split.quote = str[split.i];
		split.buffer[split.j++] = str[split.i];
	}
	else if (str[split.i] == split.quote)
	{
		split.quote = 0;
		split.buffer[split.j++] = str[split.i];
	}
	else if (ft_isspace(str[split.i]) && split.quote == 0)
	{
		if (split.j > 0)
			new_token(split.split, split.token_index, split.buffer, split.j);
		split.j = 0;
		split.token_index++;
	}
	else
		split.buffer[split.j++] = str[split.i];
	split.i++;
	return (split);
}

char	**token_split(char *str)
{
	t_splitter	split;

	split = init_s(str);
	if (!split.split || !split.buffer)
		return (NULL);
	while (str[split.i])
	{
		split = splitting(split, str);
	}
	if (split.j > 0)
	{
		new_token(split.split, split.token_index, split.buffer, split.j);
		split.token_index++;
	}
	free(split.buffer);
	split.split[split.token_index] = NULL;
	return (split.split);
}
