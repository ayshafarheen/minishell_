/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:03:37 by afarheen          #+#    #+#             */
/*   Updated: 2023/08/19 15:47:46 by afarheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
/*
Linked list of all env variables, could be used for dollar expansion
var stores left hand side and val stores right hand side
eg: HOME="/Users/afarheen"
	 |          |
	 var      val
*/
typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

int	g_exitcode;

/*
Struct for each individual command;
each command can have its own infiles and outfiles and they could be multiple
thats why its an array of strings instead of just one string. Each command
stores its array of infiles, array of outfiles, its command as well, all as
array of strings.
Eg: < in1.txt < in2.txt ls -la > out1.txt > > out2.txt

	infiles ->  | in1.txt  | in2.txt  |
	outfiles -> | out1.txt | out2.txt |
	args ->     | ls       | -la      |
*/
typedef struct s_node
{
	char			**args;
	char			**infile;
	char			**outfile;
	char			*unparsed;
	int				*o_opentype;
	int				*i_opentype;
	char			**iofiles;
	int				*oi_opentype;
	char			expansion_opt[100];
	int				infd;
	int				outfd;
	struct s_node	*next;
	int				file;
	int				flag;
	int				hd;
}	t_node;

/*
This is the main struct. It contains a linked list of all the commands (the
t_node struct). n_com is the number of commands. It also contains a linked list
of the env and the export variables.
*/
typedef struct s_minishell
{
	t_node	*commands;
	int		n_com;
	int		**pipes;
	int		*pids;
	t_env	*env;
	t_env	*expo;
	char	**envir;
	int		c;
}	t_minishell;

void	free_all(t_minishell **com_struct, int flag);
void	close_and_free2(t_minishell *com_st, t_node *cur, int *j);
char	*rl_fn(t_minishell *com_st);
void	split_parse(char *input, t_minishell *com_st);
void	main_proc(t_minishell *com_st, char **temp);
void	init_pipes(t_minishell *com_st);
int		check_builtin(t_node *cur, t_minishell *com_struct, int in, int out);
int		check_synt_err(char *input, int *i, int *nw, char *quote_type);
int		syntax_error(char *input);
void	ft_lstadd_back(t_node **lst, t_node *ele);
void	create_env(t_minishell *com_struct, char **envp);
char	*get_myenv(t_minishell *com_struct, char *var);
void	printf_arr(char **arr);
void	handler(int num);
void	ft_print(t_minishell *com_struct);
void	ft_free(char **mat);
void	ft_lstinsert(t_env **lst, t_env *ele);
void	ft_lstadd_backenv(t_env **lst, t_env *ele);
t_env	*ft_lstnewenv(char *var);
t_node	*ft_lstnew(void);
void	free_pipes(t_minishell *com_st);
void	free_command(t_minishell **com_struct);
void	convert_to_2d(t_minishell **com_struct);
int		write_error(char *cmd, char *val, char *msg, int flag);
int		open_outfiles(t_node *outfile, t_minishell *com_struct);
void	req_free(t_minishell *com_struct, int exitcode);
void	print_export(t_minishell *com_struct);
int		print_env(t_minishell *com_struct);
int		case_existance(t_minishell *com_struct, char *var);
void	set_env( char *loc, char *var, t_env *envtype);
int		exec_export(t_node *cur, t_minishell *com_struct);
void	case_notexist(t_minishell *com_struct, char *var);
int		alpha(char a);
void	execution(t_minishell *com_struct);
char	*parse_path(char *args, t_minishell **com_struct);
void	infile_fail(t_node *cur, t_minishell *com_struct, int i);
void	exec_nofail(t_minishell *com_struct, t_node *cur, int i);
void	wait_and_free(t_minishell *com_struct, int loop);
int		exec_pwd(void);
int		exec_unset(t_node *cur, t_minishell *com_struct);
char	*get_next_line(int fd);
void	close_fds(t_node *cur);
int		basic_error(t_minishell *com_struct, int exitcode, char *msg, int val);
int		isnum(char a);
void	close_pipes(t_minishell *com_struct);
void	rl_replace_line(const char *text, int clear_undo);
int		export_validation(t_node *cur);
int		exec_exit(t_node *cur, t_minishell *com_struct, int in, int out);
void	dollar_exp(t_minishell *com_struct, t_node *cur);
void	quotations(t_node *cur);
void	case_quotes_bracs(char **final, t_node *cur, int *i, int *j);
char	det_quote(t_node *cur, char *quote_type, int i, int *file);
int		calc_size(t_node *cur);
char	*apply_spacing(t_node *cur, char *final);
void	spacings(t_minishell *com_struct, t_node *cur);
char	*copy_till(char *start, char final);
char	*copy_till_end(char *start, char o);
char	*copy_till_end_single(char *start);
char	*till_first_exp( t_node *cur);
int		check_dollar_exp(t_node *cur);
char	*find_not_alnum(char *word);
void	close_and_free(int in, int out, t_minishell *com_struct, int num);
int		exec_echo(t_node *cur);
void	set_exp(t_node *cur, char q_type, int *i, int *j);
int		exec_cd(t_node *cur, t_minishell *com_struct);
void	free2(char *str, int *in, char *str2);
char	*quotations2(char *str);
int		if_sing(char *str);
void	det_fd(int *fdi, int *fdo, t_node *cur, int *vals);
int		case_outfiles(t_node *cur, int i, int fdi);
int		case_infiles(t_node *cur, int i, int fdi);
int		single_command(t_minishell *com_st);
void	exec_command(t_node *cur, t_minishell *com_struct, int i, int flag);
int		open_all(t_node *cur, t_minishell *com_struct, int flag);
int		syntax_err_2(char *input, int *i, int *nw, char *quote_type);
int		check_synt_err(char *input, int *i, int *nw, char *quote_type);

// REDIRECTION
void	redirection(t_node *cur);
void	print_redirections(t_node *cur);
int		count_args(char **args);

#endif
