/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 05:22:37 by namichel          #+#    #+#             */
/*   Updated: 2025/03/05 00:56:40 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delimiter(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (is_delimiter(s[i], c) && s[i] != '\0')
			i++;
		if (!is_delimiter(s[i], c) && s[i] != '\0')
			count++;
		while (!is_delimiter(s[i], c) && s[i] != '\0')
			i++;
	}
	return (count);
}

char	*words(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_freev(char **strv)
{
	int	i;

	i = 0;
	while (strv[i] != NULL)
	{
		free(strv[i]);
		i++;
	}
	free(strv);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		i;
	int		count;

	count = count_words(s, c);
	split = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	count = 0;
	while (s[i] && count_words(s, c) != 0)
	{
		while (is_delimiter(s[i], c) && s[i] != '\0')
			i++;
		if (!is_delimiter(s[i], c) && s[i] != '\0')
			split[count++] = words(&s[i], c);
		if (!split[count - 1])
		{
			ft_freev(split);
			return (NULL);
		}
		while (!is_delimiter(s[i], c) && s[i] != '\0')
			i++;
	}
	return (split);
}
