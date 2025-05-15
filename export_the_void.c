/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_the_void.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:55:25 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 08:30:31 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	count_line(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == 0)
		return (1);
	else if (s2[i] > s1[i])
		return (0);
	return (1);
}

char	**sort(char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i])
	{
		j = 0;
		while (table[j])
		{
			if (cmp(table[i], table[j]) == 0)
			{
				ft_swap(&(table[i]), &(table[j]));
				i--;
				break ;
			}
			j++;
		}
		i++;
	}
	return (table);
}

void	export_nothing(char **envp)
{
	char	**sort_table;
	int		tmp;

	if (!envp)
		return ;
	tmp = count_line(envp);
	sort_table = malloc(sizeof(char *) * (tmp + 1));
	if (!sort_table)
	{
		printf("failure export noting malloc");
		exit(1);
	}
	sort_table[tmp] = 0;
	while (tmp--)
		sort_table[tmp] = envp[tmp];
	sort(sort_table);
	tmp = 0;
	while (sort_table[tmp])
	{
		printf(MAGENTA "declare -x %s\n" RESET, sort_table[tmp]);
		tmp++;
	}
	free_tab(&sort_table);
}
