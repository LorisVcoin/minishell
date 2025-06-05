/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:10:46 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 17:25:40 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define W_PIPE 1
#define R_PIPE 0

/*struct stat {
	dev_t     st_dev;     // ID du périphérique contenant le fichier
	ino_t     st_ino;     // Numéro d'inode
	mode_t    st_mode;    // Mode de protection (type + permissions)
	nlink_t   st_nlink;   // Nombre de liens (hard links)
	uid_t     st_uid;     // UID du propriétaire
	gid_t     st_gid;     // GID du groupe
	dev_t     st_rdev;    // ID du périphérique (si fichier spécial)
	off_t     st_size;    // Taille totale en octets
	blksize_t st_blksize; // Taille de bloc optimale pour I/O
	blkcnt_t  st_blocks;  // Nombre de blocs alloués
	time_t    st_atime;   // Dernier accès
	time_t    st_mtime;   // Dernière modification
	time_t    st_ctime;   // Dernier changement d’état (permissions, etc)
							//
							//
							// S_IFDIR = dossier ?
							// S_IRUSR = droit pour lire ?
};
*/

int failure(char *arg)
{
	struct stat st;

	if (!strchr(arg, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}

	if (stat(arg, &st) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	if (access(arg, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	return (0);
}


//#TODO builtin . a faire
int	is_builtin(t_cmd *command)
{
	if (!command->arg)
		return (1);
	else if (ft_strcmp(command->arg[0], "pwd"))
		return (1);
	else if (ft_strcmp(command->arg[0], "echo"))
		return (1);
	else if (ft_strcmp(command->arg[0], "env"))
		return (1);
	else if (ft_strcmp(command->arg[0], "export"))
		return (1);
	else if (ft_strcmp(command->arg[0], "unset"))
		return (1);
	else if (ft_strcmp(command->arg[0], "cd"))
		return (1);
	else if (ft_strcmp(command->arg[0], "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *command, char ***envp, t_inputs *inputs)
{
	if (!command->arg)
		return (0);
	else if (ft_strcmp(command->arg[0], "pwd"))
		return (pwd());
	else if (ft_strcmp(command->arg[0], "echo"))
		return (echo(command));
	else if (ft_strcmp(command->arg[0], "env"))
		return (env(*envp));
	else if (ft_strcmp(command->arg[0], "export") && !command->arg[1])
		return (export_nothing(*envp));
	else if (ft_strcmp(command->arg[0], "export"))
		return (export(command, envp));
	else if (ft_strcmp(command->arg[0], "unset"))
		return (unset(command, envp));
	else if (ft_strcmp(command->arg[0], "cd"))
		return (cd(command, envp));
	else if (ft_strcmp(command->arg[0], "exit"))
		return (verif_exit(command, inputs));
	return (0);
}

void	exec_out_fork(t_cmd *command, char ***envp, t_inputs *inputs)
{
	if (is_builtin(command))
		g_exit = exec_builtin(command, envp, inputs);
	else
	{
		if (access(command->cmd, X_OK) == 0)
			execve(command->cmd, command->arg, *envp);
		g_exit = failure(command->arg[0]);
	}
}
#include <readline/history.h>
#include <readline/readline.h>

void	exec_in_fork(t_cmd *command, char ***envp, t_inputs *inputs)
{
	if (is_builtin(command))
	{
		g_exit = exec_builtin(command, envp, inputs);
		free_tab(envp);
		free_inputs(inputs);
		rl_clear_history();
		exit (g_exit);
	}
	else
	{
		if (access(command->cmd, X_OK) == 0)
			execve(command->cmd, command->arg, *envp);
		g_exit = failure(command->arg[0]);
		rl_clear_history();
		free_inputs(inputs);
		free_tab(envp);
		exit(g_exit);
	}
}

static int	fork_needed(t_cmd *command)
{
	if (!command->next && is_builtin(command))
		return (0);
	return (1);
}

#include <stdbool.h>

static int	open_redirections(t_cmd *cmd)
{
	if (cmd->in.file)
	{
		cmd->in.fd = open(cmd->in.file, cmd->in.flag);
		if (cmd->in.fd == -1)
		{
			g_exit = 1;
			return (1);
		}
	}
	if (cmd->out.file)
	{
		cmd->out.fd = open(cmd->out.file, cmd->out.flag, 0644);
		if (cmd->out.fd == -1)
		{
			if (cmd->in.fd > -1)
				close(cmd->in.fd);
			g_exit = 1;
			return (1);
		}
	}
	return (0);
}

void	apply_redirections(t_cmd *cmd)
{
	if (cmd->in.fd > -1)
	{
		if (dup2(cmd->in.fd, STDIN_FILENO) == -1)
			perror("dup2 infile");
		close(cmd->in.fd);
		cmd->in.fd = -1;
	}
	if (cmd->out.fd > -1)
	{
		if (dup2(cmd->out.fd, STDOUT_FILENO) == -1)
			perror("dup2 outfile");
		close(cmd->out.fd);
		cmd->out.fd = -1;
	}
}

void	close_all_fds(int prev_pipe_read, int pipe_fd[2])
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	wait_all(pid_t *pids, int count)
{
	int	status;
	int	i;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			continue ;
		}
		if (WIFEXITED(status))
			g_exit = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, sig_int);
}

void	checker(void)
{
	char c;
	ssize_t res = read(STDIN_FILENO, &c, 1);
	if (res == 0)
    	printf("EOF sur stdin (fermé ou terminé)\n");
	else if (res == -1)
		printf("Erreur de lecture stdin: %s\n", strerror(errno));
	else
    	printf("Lecture de stdin: '%c'\n", c);
}

void	exec_cmd(t_inputs *inputs, char ***envp)
{
	t_cmd	*cmd;
	pid_t	child;
	pid_t	pids[1024];
	int		pids_count;
	int		prev_pipe_read;
	bool	has_next;
	bool	need_fork;
	int		pipe_fd[2];
	int		stdin_cpy = dup(STDIN_FILENO);
	int		stdout_cpy = dup(STDOUT_FILENO);
	int		devnull = open("/dev/null", O_RDONLY);

	pids_count = 0;
	prev_pipe_read = -1;
	cmd = inputs->cmds;
	while (cmd)
	{
		//printf("%d\n", prev_pipe_read);
		has_next = (cmd->next != NULL);
		if (has_next)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				break ;
			}
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = -1;
		}
		if (open_redirections(cmd))
		{
			perror("redirections");
			g_exit = 1;
			close_all_fds(prev_pipe_read, pipe_fd);
			prev_pipe_read = devnull;
			cmd = cmd->next;
			continue ;
		}
		need_fork = fork_needed(cmd);
		if (need_fork)
		{
			child = fork();
			if (child == 0)
			{
				if (prev_pipe_read != -1)
					dup2(prev_pipe_read, STDIN_FILENO);
				if (pipe_fd[1] != -1)
					dup2(pipe_fd[1], STDOUT_FILENO);
				if (pipe_fd[0] != -1)
					close(pipe_fd[0]);
				apply_redirections(cmd);
				close_all_fds(prev_pipe_read, pipe_fd);
				close(stdout_cpy);
				close(stdin_cpy);
				close(devnull);
				exec_in_fork(cmd, envp, inputs);
				exit(EXIT_FAILURE);
			}
			else if (child < 0)
			{
				perror("fork");
				break ;
			}
			else
			{
				if (cmd->in.fd != -2)
					close(cmd->in.fd);
				if (cmd->out.fd != -2)
					close(cmd->out.fd);
				if (pids_count < 1024)
					pids[pids_count++] = child;
				else
					fprintf(stderr, "Too many process\n");
				if (prev_pipe_read != -1)
					close(prev_pipe_read);
				if (pipe_fd[1] != -1)
					close(pipe_fd[1]);
			}
		}
		else
		{
			if (prev_pipe_read != -1)
			{
				dup2(prev_pipe_read, STDIN_FILENO);
				close(prev_pipe_read);
			}
			apply_redirections(cmd);
			exec_out_fork(cmd, envp, inputs);
			if (pipe_fd[1] != -1)
				close(pipe_fd[1]);
			if (!has_next && pipe_fd[0] != -1)
				close(pipe_fd[0]);
			dup2(stdin_cpy, STDIN_FILENO);
			dup2(stdout_cpy, STDOUT_FILENO);
		}
		prev_pipe_read = pipe_fd[0];
		cmd = cmd->next;
	}
	close(devnull);
	close(stdin_cpy);
	close(stdout_cpy);
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	wait_all(pids, pids_count);
}

/*
// EXEC FINAL JESPERE EN TT CAS
void	exec_cmd(t_inputs *inputs, char ***envp)
{
	t_cmd	*command;
	int		pipe_fd[2];
	int		prev_pipe_fd;
	pid_t	child;
	pid_t	last_pid = -1;
	int		status;
	int		need_pipe;
	int		in_pipeline;
	int		forked_any = 0;
//	print_cmd(inputs);

	command = inputs->cmds;
	prev_pipe_fd = -1;
	verif_exit(command, inputs);
	while (command)
	{
		need_pipe = 0;
		// créer un pipe uniquement si 0 redirection définie
		if (command->next && command->out.fd != -1 && command->in.fd != -1)
		{
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			need_pipe = 1;
		}
//		printf("%d\n", need_pipe);
		in_pipeline = (command->next != NULL || prev_pipe_fd != -1);
		if (!in_pipeline && env_buitin(command))
		{
			is_buitin(command, envp, inputs);
			command = command->next;
			continue ;
		}
		if (command->in.fd < 0 || command->out.fd < 0)
		{
			if (prev_pipe_fd != -1)
				close(prev_pipe_fd);
			if (command->next && command->out.fd == -1)
				close(pipe_fd[1]);
			if (command->next && command->in.fd == -1)
				close(pipe_fd[0]);
			g_exit = 1;
			prev_pipe_fd = -1;
			command = command->next;
			continue ;
		}
		child = fork();
		if (child == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child == 0)
		{
			//printf("le fd:%d\nle file:%s\n", command->in.fd, command->in.file);
			// entrée
			if (command->in.file)
			{
//				printf("%d", command->in.fd);
				dup2(command->in.fd, STDIN_FILENO);
				close(command->in.fd);
			}
			else if (prev_pipe_fd != -1)
			{
				dup2(prev_pipe_fd, STDIN_FILENO);
				close(prev_pipe_fd);
			}
			// sortie
			if (command->out.file)
			{
				dup2(command->out.fd, STDOUT_FILENO);
				close(command->out.fd);
			}
			else if (need_pipe)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
			}
			exec(command, envp, inputs);
			perror("exec failed");
			exit(EXIT_FAILURE);
		}
		last_pid = child;
		forked_any = 1;
		//printf("%d\n", g_exit);
		// fermeture propre des fd
		if (prev_pipe_fd != -1)
			close(prev_pipe_fd);
		if (command->in.file)
			close(command->in.fd);
		if (command->out.file)
			close(command->out.fd);
		if (need_pipe)
		{
			close(pipe_fd[1]);         // fermer écriture dans parent
			prev_pipe_fd = pipe_fd[0]; // lecture prochaine commande
		}
		else
		{
			prev_pipe_fd = -1;
		}
//		printf("%d\n", g_exit);
		command = command->next;
	}
	if (forked_any)
	{
		pid_t	wpid;
		int	exit_code = 0;
		while ((wpid = wait(&status)) > 0)
		{
			if (wpid == last_pid)
			{
				if (WIFEXITED(status))
					exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					exit_code = 128 + WTERMSIG(status);
			}
		}
		g_exit = exit_code;
	}
}*/
