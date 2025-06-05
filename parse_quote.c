// int	i;
// int	start;
// int	end;
// 
// i = 0;
// start = -1;
// end = -1;
// while (str[i])
// {
// printf("str[%d] = %c ;\n", i, str[i]);
// if (str[i] == c)
// return (str);
// if (str[i] == set[0])
// {
// start = i;
// i++;
// while (str[i])
// {
// if (str[i] == set[0])
// {
// end = i;
// printf("%d\n", start);
// printf("%d\n", i);
// str = new_str(str, start, end);
// end = -1;
// break ;
// }
// printf("%d\n", i);
// i++;
// }
// }
// if (str[i])
// i++;
// }
// if (start == -1 || end == -1)
// return (str);
// str = new_str(str, start, end);
// if (!str)
// return (0);

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 21:00:58 by lviravon          #+#    #+#             */
/*   Updated: 2025/05/31 00:37:34 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*new_str_(char *new_str, int i, int i2, char *str)
{
	while (str[i])
	{
		while (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				new_str[i2++] = str[i++];
		}
		while (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				new_str[i2++] = str[i++];
		}
		new_str[i2++] = str[i];
		if (str[i])
			i++;
	}
	new_str[i2] = '\0';
	return (new_str);
}

static int	count_supr_quote(char *str)
{
	int	i;
	int	supr;

	i = 0;
	supr = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			supr++;
			i++;
			while (str[i] != '\"')
			{
				if (!str[i])
					return (-1);
				i++;
			}
			supr++;
		}
		if (str[i] == '\'')
		{
			supr++;
			i++;
			while (str[i] != '\'')
			{
				if (!str[i])
					return (-1);
				i++;
			}
			supr++;
		}
		i++;
	}
	return (supr);
}

char	*verif_quote(char *str)
{
	int		i;
	int		i2;
	int		quote;
	int		size;
	char	*new_str;

	i = 0;
	i2 = 0;
	quote = count_supr_quote(str);
	if (quote == -1)
		return (str);
	size = ft_strlen(str) - quote;
	new_str = malloc(size + 2);
	new_str = new_str_(new_str, i, i2, str);
	free(str);
	return (new_str);
}

static char	**copy_str(char **split, char *tmp, int i)
{
	(void)tmp;
	while (split[i])
	{
		split[i] = verif_quote(split[i]);
		if (!split[i])
			return (0);
		i++;
	}
	return (split);
}

char	**supre_quote(char **split)
{
	split = copy_str(split, "", 0);
	if (!split)
		return (0);
	return (split);
}
