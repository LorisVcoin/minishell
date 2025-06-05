/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:44:56 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 18:58:08 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

int		g_exit = 0;
/*

struct termios {
	tcflag_t c_iflag;  // Flags d'entrée
	tcflag_t c_oflag;  // Flags de sortie
	tcflag_t c_cflag;  // Flags de contrôle
	tcflag_t c_lflag;  // Flags locaux (lflags)
	cc_t c_line;       // Ligne de terminal
	cc_t c_cc[VEND];   // Valeurs pour des caractères spéciaux
}
*/

void	sig_int(int n)
{
	if (n == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_quit(int n)
{
	if (n == SIGQUIT)
		rl_redisplay();
}

void	init_inputs(t_inputs *inputs)
{
	inputs->loop_status = 1;
}

static int	is_all_spaces(char *terminal)
{
	int	i;

	i = 0;
	while (terminal[i] == ' ' || (terminal[i] >= 9 && terminal[i] <= 13))
		i++;
	if (terminal[i] == '\0')
	{
		g_exit = 0;
		return (1);
	}
	i = 0;
	return (0);
}

void	minishell_loop(char ***envp)
{
	char		*terminal;
	t_inputs	inputs;

	init_inputs(&inputs);
	while (inputs.loop_status)
	{
		terminal = readline("Naminishell$>");//#TODO gerer ENTREE
		if (terminal == 0)
		{
			rl_clear_history();
			ft_putstr_fd("exit\n", 2);
			inputs.loop_status = 0;
			break ;
		}
		if (terminal && *terminal != '\0')
			add_history(terminal);
		if (is_all_spaces(terminal))
		{
			free_string(&terminal);
			continue ;
		}
		if (terminal)
			terminal = parsing(&inputs, terminal, *envp);
		if (terminal != NULL)
		{
			free_string(&terminal);
			exec_cmd(&inputs, envp);
			free_inputs(&inputs);
		}
		else
			g_exit = 2;
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	old;
	struct termios	new;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &old);
	new = old;
	new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	// welcome() #TODO
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
	envp = dup_env(envp);
	if (envp)
		minishell_loop(&envp);
	tcsetattr(STDIN_FILENO, 0, &old);
	free_tab(&envp);
	return (g_exit);
}
