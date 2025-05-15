/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:10:46 by namichel          #+#    #+#             */
/*   Updated: 2025/04/17 08:45:56 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

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

int	failure(char *file)
{
	struct stat	st;

	if (stat(file, &st) == -1)
	{
		printf("error stat\n");
		return (0);
	}
	if (st.st_mode & S_IFDIR)
		printf("FAILURE %s is a directory\n", file);
	else if (!(st.st_mode & S_IFDIR || st.st_mode & S_IRUSR))
		printf("permission denied for %s\n", file);
	return (0);
}

int	is_buitin(t_cmd *command, char **envp)
{
	if (command->arg == 0)
		exit (0);
	(void)envp;
	if (ft_strcmp(command->arg[0], "pwd"))
	{
		//pwd() #TODO
		return (1); // exit0 qd fix
	}
	if (ft_strcmp(command->arg[0], "export"))
	{
		export_nothing(envp);
		exit (0);
	}
	if (ft_strcmp(command->arg[0], "echo"))
	{
		echo(command);
		exit (0);
	}
	if (ft_strcmp(command->arg[0], "env"))
	{
		env(envp);
		exit (0);
	}
	return (1);
}

void	exec(t_cmd *command, char **envp, int *exit)
{
	*exit = is_buitin(command, envp);
	if (access(command->cmd, X_OK) == 0)
		execve(command->cmd, command->arg, envp);
	else
		printf("Command not found\n");
}

void	subprocess(t_cmd *command, char **envp, int inf_ouf[2], int *exit)
{
	pid_t	child;
	int		fd[2];

	if (command->next != NULL)
		pipe(fd);
	child = fork();
	if (child == -1)
		printf("child KILLED\n");
	else if (child == 0)
	{
		dup2(inf_ouf[0], STDIN_FILENO); //TODO GERER LES PERROR
		if (command->next != NULL)
			dup2(fd[W_PIPE], STDOUT_FILENO);
		else
			dup2(inf_ouf[1], STDOUT_FILENO);
		close(fd[R_PIPE]);
		exec(command, envp, exit);
	}
	else
	{
		waitpid(child, exit, 0);
		*exit = WEXITSTATUS(*exit);
		close(fd[W_PIPE]);
		inf_ouf[0] = fd[R_PIPE];
	}
}

int	open_file(t_file inf, t_file ouf, int inf_ouf[2])
{
	int	fd;

	if (inf.file != 0)
	{
		//if (inf.eof)
			//HEREDOC TODO
		fd = open(inf.file, inf.flag);
		if (fd == -1)
			return (failure(inf.file));
		else
			inf_ouf[0] = fd;
	}
	if (ouf.file != 0)
	{
		fd = open(ouf.file, ouf.flag);
		if (fd == -1)
			return (failure(ouf.file));
		else
			inf_ouf[1] = fd;
	}
	return (1);
}

void	exec_cmd(t_inputs *inputs, char ***envp)
{
	t_cmd	*command;
	int		inf_ouf[2];
	int		g_exit = 0;

	command = inputs->cmds;
	while (command != NULL)
	{
		if (!open_file(command->in, command->out, inf_ouf))
			return ;
		if (ft_strcmp(command->arg[0], "exit") && command->next == 0)
			inputs->loop_status = 0;
		subprocess(command, *envp, inf_ouf, &g_exit); //TODO EXIT VALUE
		command = command->next;
	}
	if (inf_ouf[1] != 1)
		close(inf_ouf[1]);
}
