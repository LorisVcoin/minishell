/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:53:00 by namichel          #+#    #+#             */
/*   Updated: 2025/05/31 02:15:24 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
/*
static int	explain_failure(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		fprintf(stderr, "cd: %s: No such file or directory\n", path);
		return (EXIT_FAILURE);
	}
	if (!(st.st_mode & S_IFDIR))
		fprintf(stderr, "cd : not a directory: %s\n", path);
	else if (!(st.st_mode & S_IXUSR))
		fprintf(stderr, "cd: permission denied: %s\n", path);
	return (EXIT_SUCCESS);
}*/

void	refresh_env(char ***env, char *oldpath)
{
	char	*pwd;
	char	*newpwd;
	char	*oldpwd;

	pwd = getpwd();
	newpwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	exp_pwd(env, newpwd);
	free(newpwd);
	oldpwd = ft_strjoin("OLDPWD=", oldpath);
	exp_pwd(env, oldpwd);
	free(oldpwd);
}

int	cd(t_cmd *command, char ***envp)
{
	char	*home;
	char	*oldpath;

	oldpath = getpwd();
	if (command->arg[2] != 0)
	{
		fprintf(stderr, "cd: too many arguments\n");
		free(oldpath);
		return (EXIT_FAILURE);
	}
	if (command->arg[1] != 0)
	{
		if (chdir(command->arg[1]) != -1)
			refresh_env(envp, oldpath);
		else
		{
			perror("cd");
			free(oldpath);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		home = my_getenv("HOME", *envp);
		if (chdir(home) == 0)
			refresh_env(envp, oldpath);
		else
			perror("cd");
	}
	free(oldpath);
	return (EXIT_SUCCESS);
}
