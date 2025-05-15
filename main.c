/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:44:56 by namichel          #+#    #+#             */
/*   Updated: 2025/04/18 01:41:57 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libft/get_next_line.h>
#include <libft/libft.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <termios.h>
#include <unistd.h>

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

void	init_inputs(t_inputs *inputs)
{
	inputs->loop_status = 1;
}

void	minishell_loop(char ***envp)
{
	char		*terminal;
	t_inputs	inputs;

	// (void)envp;
	init_inputs(&inputs);
	while (inputs.loop_status)
	{
		terminal = readline("God is gread$>");
		if (terminal == 0)
		{
			rl_clear_history();
			printf("exit\n");
			inputs.loop_status = 0;
			exit(0);
		}
		add_history(terminal);
		if (terminal)
			terminal = parsing(&inputs, terminal, *envp);
		if (terminal)
			exec_cmd(&inputs, envp);
		free_inputs(&inputs);
		free_string(&terminal);
	}
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
	envp = dup_env(envp);
	while (envp)
		minishell_loop(&envp);
	tcsetattr(STDIN_FILENO, 0, &old);
	free_tab(&envp);
	return (0);
}
