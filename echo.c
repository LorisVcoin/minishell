/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 06:37:53 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 17:49:52 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char **command)
{
	int	i;

	i = 0;
	while (command[++i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			write(1, " ", 1);
	}
}

int	echo(t_cmd *command)
{
	if (command->arg[1] != 0)
	{
		if (ft_strcmp(command->arg[1], "-n") != 0)
			echo_cmd(&(command->arg[1]));
		else
		{
			echo_cmd(&(command->arg[0]));
			write(1, "\n", 1);
		}
	}
	else
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
