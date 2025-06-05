/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 06:04:36 by namichel          #+#    #+#             */
/*   Updated: 2025/05/27 18:41:02 by namichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <unistd.h>

char	*getpwd(void)
{
	char			*pwd;
	int				errno;
	unsigned int	i;

	pwd = malloc(64);
	if (pwd == 0)
		return (0);
	getcwd(pwd, 64);
	i = 2;
	while (errno == ERANGE)
	{
		free(pwd);
		errno = 0;
		pwd = malloc(64 * i);
		if (pwd == 0)
			return (0);
		getcwd(pwd, 64 * i);
		i++;
	}
	return (pwd);
}

int	pwd(void)
{
	char	*pwd;

	pwd = getpwd();
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
