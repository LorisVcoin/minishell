/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:13:50 by namichel          #+#    #+#             */
/*   Updated: 2025/05/15 19:10:48 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>

// Reset
# define RESET "\033[0m"

// Text colors (classiques)
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

typedef enum
{
	TEXT, // command ou arg
	COMMAND,
	PIPE,    // pipeline
	R_IN,    // '<'
	R_OUT,   // '>'
	HEREDOC, // '<<'
	APPEND,  // '>>'
	FILE_TXT
}					type_token;

extern int			g_exit;

typedef struct s_file
{
	char			*eof;
	char			*file;
	int				flag;
}					t_file;

typedef struct s_cmd
{
	t_file			in;
	t_file			out;
	char			*cmd;
	char			**arg;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_inputs
{
	t_file			in;
	t_file			out;
	t_cmd			*cmds;
	int				loop_status;
}					t_inputs;

typedef struct s_splitter
{
	char		**split;
	int			i;
	int			j;
	char		*buffer;
	char		quote;
	int			token_index;
}					t_splitter;

void				print_cmd_arg(t_cmd *cmd);
void				print_file(t_file *f, char *in_or_out);
void				print_cmd(t_inputs *inputs);
void				print_tab(char **tab);
char				**dup_env(char **envp);

char				*parsing(t_inputs *inputs, char *line, char **envp);
char				*space_pipe(char *line, int i);
char				*space_redirec(char *line, int i, char c);
int					ft_isspace(char c);
char				*varexp_envp(char **envp, char *line);
void				new_token(char **split, int j, char *buffer, int len);
char				**token_split(char *str);
char				*space_char(char *line, int i, char c);
char				*supressed_double_quote(char *line, int firPlace,
						int secPlace);

int					ft_strcmp(char *s1, char *s2);
t_cmd				*new_cmd(void);
void				fill_infos(char **split, t_cmd *inputs, int *i);
int					next_cmd(t_cmd **ptr);
char				**concatanate(char **args, char *new);
char				*expend_equal(char *s);
char				*my_getenv(char *s, char **envp);
char				*path_conca(char *s1, char *s2);
void				path(t_cmd *cmd, char **envp);
void				cmd_dup(char **split, char **envp, int *i, t_cmd *ptr);
void				set_cmd(t_inputs *inputs, char **split, char **envp);

void				exec(t_cmd *command, char **envp, int *exit);
void				subprocess(t_cmd *command, char **envp, int inf_ouf[2],
						int *exit);
int					open_file(t_file inf, t_file ouf, int inf_ouf[2]);
void				exec_cmd(t_inputs *inputs, char ***envp);

void				free_string(char **str);
void				free_cmds(t_cmd *command);
void				free_inputs(t_inputs *inputs);
void				free_tab(char ***tab);

void				echo_cmd(char **command);
void				echo(t_cmd *command);

int					where_is_equal(char *envp);
void				env(char **envp);

int					count_line(char **envp);
void				ft_swap(char **a, char **b);
int					cmp(char *s1, char *s2);
char				**sort(char **table);
void				export_nothing(char **envp);

#endif
