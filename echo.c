/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 06:37:53 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 07:33:11 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	echo_cmd(char **command)
{
	int	i;

	i = 0;
	while (command[++i])
	{
		printf(GREEN "%s" RESET, command[i]);
		if (command[i + 1] != 0)
			printf(" ");
	}
}

void	echo(t_cmd *command)
{
	if (command->arg[1] != 0)
	{
		if (ft_strcmp(command->arg[1], "-n") != 0)
			echo_cmd(&(command->arg[1]));
		else
		{
			echo_cmd(&(command->arg[0]));
			printf("\n");
		}
	}
	else
		printf("\n");
}
