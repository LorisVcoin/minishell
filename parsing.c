/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:36:28 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 19:52:16 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmmp(char *s1, char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (-1);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (0);
}

void	print_cmd_arg(t_cmd *cmd)
{
	int	i;
	int	cmd_count;

	cmd_count = 1;
	while (cmd)
	{
		print_file(&cmd->in, "INFILE");
		print_file(&cmd->out, "OUTFILE");
		printf("Commande numero: %d\n", cmd_count++);
		if (cmd->cmd)
			printf("cmd: %s\n", cmd->cmd);
		else
			printf("cmd: (null)\n");
		if (cmd->arg)
		{
			for (i = 0; cmd->arg[i]; i++)
				printf("arg[%d]: %s\n", i, cmd->arg[i]);
		}
		else
			printf("args: (null)\n");
		cmd = cmd->next;
	}
}

void	print_file(t_file *f, char *in_or_out)
{
	printf("-->%s<--\n", in_or_out);
	if (f->file)
		printf("File: %s\n", f->file);
	else
		printf("File: (null)\n");
	if (f->eof)
		printf("EOF: %s\n", f->eof);
	else
		printf("EOF: (null)\n");
	printf("FLAG: %d\n", f->flag);
}

void	print_cmd(t_inputs *inputs)
{
	printf("---STRUCTURE CHECKING---\n");
	printf("LOOP = %d\n", inputs->loop_status);
	print_cmd_arg(inputs->cmds);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
	free_tab(&tab);
}

static int	search(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}
/*
static int	is_redirections(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	check_structure(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		if (cmd->arg)
		{
			i = 0;
			if (is_redirections(cmd->arg[i][0]))
				return (0);
			i++;
		}
		cmd = cmd->next;
	}
	return (1);
}
*/

char	**tab_syntax(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[0], "|"))
		{
			free_tab(&tab);
			return (NULL);
		}
		if ((is_redirections(tab[i]) || ft_strcmp(tab[i], "|")) && ft_strcmp(tab[i + 1], "|"))
		{
			//printf("hi");
			free_tab(&tab);
			return (NULL);
		}
		i++;
	}
	if (is_redirections(tab[i - 1]) || ft_strcmp(tab[i - 1], "|"))
	{
		free_tab(&tab);
		return (NULL);
	}
	return (tab);
}

static char **skip_voidarg(char **split)
{
	int		i;
	int		j;
	char	**res;

	j = 0;
	i = 0;
	res = ft_calloc(sizeof(char *) * (count_line(split)), 2);
	while (split[i])
	{
		if (ft_strcmp(split[i], ""))
		{
			i++;
			continue ;
		}
		res[j] = ft_strdup(split[i]);
		j++;
		i++;
	}
	free_tab(&split);
	return (res);
}

#include <string.h>
//#TODO Reste a faire "| | | ou | > -----> ? = 2"
char	*parsing(t_inputs *inputs, char *line, char **envp)
{
	char	**split;
	int		i;
	int		bexpand;

	bexpand = 0;
	i = 0;
	if (line[0] == 0)
		return (0);
	line = cut_space(line);
	if (line)
		line = exitval(line);
	if (line)
		line = space(line);
	// printf("%s\n", line);
	if (line)
		if (line[0] == '|' || line[0] == '\n')
			return (0);
	if (!line)
		return (0);
	split = token_split(line);
	// print_tab(split);
	while (split[i])
	{
		if (ft_strcmmp(split[i], "<<") == 0 && search(split[i], '\''))
		{
			i++;
			bexpand = -1;
		}
		if (bexpand != -1 && split[i] && search(split[i], '$'))
			split[i] = expand(split[i], envp);
		if (split[i])
			i++;
		bexpand = 0;
	}
	if (split)
		split = tab_syntax(split);
	if (split)
		split = skip_voidarg(split);
	// if (split)
		// split = supre_quote(split);
	if (split)
		set_cmd(inputs, split, envp);
	// inputs->term = line;
	// print_cmd(inputs);
	// if (!check_structure(inputs->cmds))
		// return (0);
	// printf("%s\n", inputs->cmds->cmd);
	// if (!inputs->cmds->cmd)
		// return (0);
	if (!split)
		free_string(&line);
	return (line);

}
