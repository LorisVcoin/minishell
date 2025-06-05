/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namichel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 23:13:50 by namichel          #+#    #+#             */
/*   Updated: 2025/06/04 19:17:45 by namichel         ###   ########.fr       */
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

extern int	g_exit;

typedef struct s_token
{
	int		len;
	int		type;
	int		td;
	int		tmp;
}			t_token;

typedef struct s_file
{
	char *eof;  // EOF pour heredoc
	char *file; // Nom du fichier
	int flag;   // flag du fichier
	int		fd;
}			t_file;

typedef struct s_cmd
{
	t_file in;          // data infile
	t_file out;         // data outfile
	char *cmd;          // PATH pour executer la commande
	char **arg;         // arguments de la commande
	struct s_cmd *next; // commande suivante pour chaque pipe
}			t_cmd;

typedef struct s_inputs
{
	t_cmd	*cmds;
	int loop_status; // 1 ou loop / 0 exit
}			t_inputs;

void		print_cmd_arg(t_cmd *cmd);
void		print_file(t_file *f, char *in_or_out);
void		print_cmd(t_inputs *inputs);
void		print_tab(char **tab);
char		**dup_env(char **envp);

char		*parsing(t_inputs *inputs, char *line, char **envp);
char		*space_pipe(char *line, int i);
char		*space_redirec(char *line, int i, char c);
int			ft_isspace(char c);
char		*varexp_envp(char **envp, char *line);
void		new_token(char **split, int j, char *buffer, int len);
char		**token_split(char *str);
char		*space_char(char *line, int i, char c);
char		*supressed_double_quote(char *line, int firPlace, int secPlace);

int			ft_strcmp(char *s1, char *s2);
t_cmd		*new_cmd(void);
int		fill_infos(char **split, t_cmd *inputs, int *i);
int			next_cmd(t_cmd **ptr);
char		**concatanate(char **args, char *new);
char		*expend_equal(char *s);
char		*my_getenv(char *s, char **envp);
char		*path_conca(char *s1, char *s2);
void		path(t_cmd *cmd, char **envp);
void		cmd_dup(char **split, char **envp, int *i, t_cmd *ptr);
int		set_cmd(t_inputs *inputs, char **split, char **envp);

void		exec(t_cmd *command, char ***envp, t_inputs *inputs);
void		subprocess(t_cmd *command, char ***envp, int inf_ouf[2], int *exit);
int			open_file(t_file inf, t_file ouf, int inf_ouf[2]);
void		exec_cmd(t_inputs *inputs, char ***envp);

void		free_string(char **str);
void		free_cmds(t_cmd *command);
void		free_inputs(t_inputs *inputs);
void		free_tab(char ***tab);

void		echo_cmd(char **command);
int			echo(t_cmd *command);

int			where_is_equal(char *envp);
int			env(char **envp);

int			count_line(char **envp);
void		ft_swap(char **a, char **b);
int			cmp(char *s1, char *s2);
char		**sort(char **table);
int			export_nothing(char **envp);

char		**dupp_and_add(char **env, char *add, int pos);
void		exp_pwd(char ***envp, char *new_pwd);
int			export(t_cmd *command, char ***envp);

size_t		count_bytes(char **env, int pos);
char		**unset_env(char **env, size_t pos);
int			unset(t_cmd *command, char ***envp);

char		*getpwd(void);
int			pwd(void);

void		refresh_env(char ***env, char *oldpath);
int			cd(t_cmd *command, char ***envp);

void		heredoc(char *eof);

int			ok_or_not(char *line, char *pos);
char		*verif_quote(char *str);
char		*cut_space(char *line);
char		*ft_strndup(char *str, int len);
char		*expand(char *line, char **envp);
char		*exitval(char *line);
char		*space(char *line);
char		**supre_quote(char **split);

int			failure(char *file);

int			b_exit(t_cmd *command, t_inputs *inputs);
int			verif_exit(t_cmd *cmd, t_inputs *inputs);

int			env_name(char c);
void		sig_int(int n);

int			is_redirections(char *str);

#endif
