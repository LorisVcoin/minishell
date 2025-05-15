/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:36:28 by namichel          #+#    #+#             */
/*   Updated: 2025/04/18 01:12:57 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/libft.h>

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

char	*parsing(t_inputs *inputs, char *line, char **envp)
{
	char	**split;
	char	c;
	int		i;
	int		tmp;

	i = 0;
	(void)inputs;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i];
			i++;
			if (line[i] != c)
				while (line[i] != c)
					i++;
		}
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			tmp = i;
			c = line[i];
			if (line[i] == '|')
				line = space_pipe(line, tmp);
			if(line[i] == '>' || line[i] == '<')
				line = space_redirec(line, tmp, c);
		}
		i++;
	}
	line = varexp_envp(envp, line);
	printf("%s\n", line);
	//remplacer "$HOME" par sa valeur mais pas '$HOME'
	split = token_split(line);
	// ! RAPPEL SUPRIMER LES " et ' après le split
	// print_tab(split);
	set_cmd(inputs, split, envp);
	//print_cmd(inputs);
	return (line);
}
