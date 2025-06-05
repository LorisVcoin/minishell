/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:02:58 by lviravon          #+#    #+#             */
/*   Updated: 2025/05/29 18:41:48 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verif_arg(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->arg[1][i] == '+' || cmd->arg[1][i] == '-')
		i++;
	while (cmd->arg[1][i])
	{
		if (!ft_isdigit(cmd->arg[1][i]))
		{
			g_exit = 2;
			return (2);
		}
		i++;
	}
	return ((unsigned char)ft_atoi(cmd->arg[1]));
}

static int	count_args(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd->arg[count])
		count++;
	return (count);
}

int	b_exit(t_cmd *cmd, t_inputs *inputs)
{
	int	get_exit;

	(void)(*inputs);
	if (count_args(cmd) >= 3)
	{
		g_exit = 1;
		return (g_exit);
	}
	else
	{
		get_exit = verif_arg(cmd);
		if (get_exit == 2)
		{
			ft_putstr_fd("exit : ", 2);
			ft_putstr_fd(cmd->arg[1], 2);
			ft_putstr_fd(" : numeric argument required\n", 2);
		}
	}
	g_exit = get_exit;
	return (g_exit);
}

int	verif_exit(t_cmd *cmd, t_inputs *inputs)
{
	if (cmd->next == NULL)
	{
		if (ft_strcmp(cmd->arg[0], "exit") && cmd->arg[1])
		{
			b_exit(cmd, inputs);
			if (g_exit == 1)
			{
				ft_putstr_fd("exit : too many arguments\n", 2);
				return (EXIT_FAILURE);
			}
			else
			{
				inputs->loop_status = 0;
				ft_putstr_fd("exit\n", 2);
				return (g_exit);
			}
		}
		else if (ft_strcmp(cmd->arg[0], "exit") && !cmd->arg[1])
		{
			ft_putstr_fd("exit\n", 2);
			inputs->loop_status = 0;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
/*
int	plus_or_minus(char c)
{
	if (c == '-' || c == '+')
		return (1);
	return (0);
}

int	str_is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		if (!plus_or_minus(str[i]))
			return (0);
	}
	return (1);
}

int	mini_exit(t_cmd *cmd, t_inputs *inputs)
{
	if (!cmd->next)
	{	
		inputs->loop_status = 0;
		return (verif_arg(cmd));
	}
	else
	{
		if (!cmd->arg[2])
				return(verif_arg(cmd));
		}
		else
		{

		}
	}
}*/
