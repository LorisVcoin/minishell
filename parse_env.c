/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 03:25:17 by namichel          #+#    #+#             */
/*   Updated: 2025/05/28 21:36:27 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *str, int len)
{
	char	*res;

	res = ft_calloc((len * 2 + 1), 1);
	if (!res)
		return (0);
	res[len] = 0;
	while (len--)
		res[len] = str[len];
	return (res);
}

/* Take the size of the expanded variable and get expanded variable.
 * VALUE RETURN :
 * 0 ERROR.
 * String containing expanded variable.*/
static char	*len_env(char *line, char **envp, int *i, int *len)
{
	char	*env;
	char	*var;
	int		start;

	start = *i;
	while (env_name(line[*i]))
		(*i)++;
	var = ft_strndup((line + start), *i - start);
	env = my_getenv(var, envp);
	if (!env)
	{
		free_string(&var);
		return (0);
	}
	free_string(&var);
	if (len)
		*len += ft_strlen(env);
	return (env);
}

static void	simple(char *res, char *line, int idx[5])
{
	res[idx[1]++] = line[idx[0]++];
	while (line[idx[0]] && line[idx[0]] != '\'')
		res[idx[1]++] = line[idx[0]++];
	res[idx[1]++] = line[idx[0]++];
}

/* Verif variable meets the standard*/
int	env_name(char c)
{
	if (c == '_')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

static void	dollar(char *res, char *line, int idx[5], char **envp)
{
	char	*env;

	if (env_name(line[idx[0]]))
	{
		env = len_env(line, envp, &idx[0], 0);
		idx[2] = 0;
		while (env && env[idx[2]])
			res[idx[1]++] = env[idx[2]++];
	}
	else
		res[idx[1]++] = '$';
}

/* Init the index pointer: 
 * index 0 = 0;
 * index 1 = 1;
 * index 2 = 0*/
static void	init_index_len(int idx[3])
{
	idx[0] = 0;
	idx[1] = 1;
	idx[2] = 0;
}

/* Either get the length of the expanded variable or simply increment idx[2] */
static void	new_dollar(int idx[3], char *line, char **envp)
{
	if (env_name(line[idx[0]]))
		len_env(line, envp, &(idx[0]), &(idx[2]));
	else
		idx[2]++;
}

/* This fonction calcul the len of the line.
 * VALUE RETURN : 
 * -1 ERROR.
 *  Length of the line */
static int	len(char *line, char **envp)
{
	int	idx[3];

	init_index_len(idx);
	while (line[idx[0]])
	{
		if (line[idx[0]] == '\"' && ++idx[0] && ++idx[2])
			idx[1] = (idx[1] + 1) % 2;
		while (idx[1] && line[idx[0]] == '\'' && idx[0])
		{
			idx[2] += 2;
			while (line[idx[0]] && line[idx[0]] != '\'' && ++idx[0])
				idx[2]++;
			if (line[idx[0]] == 0)
				return (-1);
			idx[0]++;
		}
		while (line[idx[0]] == '$' && ++idx[0])
			new_dollar(idx, line, envp);
		while (line[idx[0]] && line[idx[0]] != '\"' && (line[idx[0]] != '\''
				|| !idx[1]) && line[idx[0]] != '$' && ++idx[0])
			idx[2]++;
	}
	if (idx[1] == 0)
		return (-1);
	return (idx[2]);
}

/* Init the index pointer index 0 = 0, 1 and 2 same for index 3 = 1 and.
 * index 4 = len(line, envp). 
 * VALUE RETURN : 
 * 0 ERROR.
 * Allocate a new line with the correct size */
static char	*init_idx(int idx[5], char *line, char **envp)
{
	char	*res;

	idx[0] = 0;
	idx[1] = 0;
	idx[2] = 0;
	idx[3] = 1;
	idx[4] = len(line, envp);
	if (idx[4] == -1)
	{
		free(line);
		return (0);
	}
	res = malloc(idx[4] + 1);
	if (!res)
		return (0);
	return (res);
}

/* Expand the variable with the line and envp */
char	*expand(char *line, char **envp)
{
	char	*res;
	int		idx[5];

	res = init_idx(idx, line, envp);
	if (!res)
		return (0);
	res[idx[4]] = 0;
	while (line[idx[0]])
	{
		if (line[idx[0]] == '\"')
		{
			res[idx[1]++] = line[idx[0]++];
			idx[3] = (idx[3] + 1) % 2;
		}
		while (line[idx[0]] == '\'' && idx[3])
			simple(res, line, idx);
		while (line[idx[0]] == '$' && ++idx[0])
			dollar(res, line, idx, envp);
		while (line[idx[0]] && (line[idx[0]] != '\"' || idx[3])
			&& (line[idx[0]] != '\'' || !idx[3]) && line[idx[0]] != '$')
			res[idx[1]++] = line[idx[0]++];
	}
	free(line);
	return (res);
}
