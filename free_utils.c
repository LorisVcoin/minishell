/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 06:09:21 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 05:53:10 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_string(char **str)
{
	if (*str == 0)
		return ;
	free(*str);
	*str = 0;
}

void	free_cmds(t_cmd *command)
{
	free_string(&(command->in.file));
	command->in.flag = 0;
	free_string(&(command->out.file));
	command->out.flag = 0;
	free_string(&(command->in.eof));
	if (command->next)
	{
		free_cmds(command->next);
		free(command->next);
	}
	free(command->cmd);
	free_tab(&(command->arg));	
}

void	free_inputs(t_inputs *inputs)
{
	if (inputs->cmds)
	{
		free_cmds(inputs->cmds);
		free(inputs->cmds);
		inputs->cmds = 0;
	}
}

void	free_tab(char ***tab)
{
	int	i;

	if (*tab == 0)
		return ;
	i = 0;
	while (tab[0][i])
		i++;
	while (i--)
	{
		free_string(&(tab[0][i]));
	}
	free(*tab);
	*tab = 0;
}
