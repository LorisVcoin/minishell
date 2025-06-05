/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exitval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:48:58 by namichel          #+#    #+#             */
/*   Updated: 2025/05/28 18:39:06 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count(char *line, int ev_len)
{
	int		res;

	res = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			line++;
			res++;
			while (*line && *line != '\'')
			{
				line++;
				res++;
			}
		}
		if (*line == '$' && *(line + 1) == '?')
		{
			line += 2;
			res += ev_len;
		}
		if (*line)
		{
			line++;
			res++;
		}
	}
	return (res);
}


//#TODO PROTECTION MALLOC STRDUP
static void	replace(char *res, char *line, char *ev)
{
	int	i;

	while (*line)
	{
		if (*line == '\'')
		{
			*res = *line;
			line++;
			res++;
			while (*line && *line != '\'')
			{
				*res = *line;
				line++;
				res++;
			}
		}
		if (*line == '$' && *(line + 1) == '?')
		{
			line += 2;
			i = 0;
			while (ev[i])
			{
				*res = ev[i];
				res++;
				i++;
			}
		}
		if (*line)
		{
			*res = *line;
			res++;
			line++;
		}
	}
}

char	*exitval(char *line)
{
	int		res_len;
	int		ev_len;
	char	*ev;
	char	*res;

	ev = ft_itoa(g_exit);
	ev_len = ft_strlen(ev);
	res_len = count(line, ev_len);
	res = malloc(res_len + 1);
	if (res == NULL)//#TODO !
		return (0);
	res[res_len] = 0;
	replace(res, line, ev);
	free(ev);
	free(line);
	return (res);
}
