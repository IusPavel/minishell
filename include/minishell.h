/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: signacia <signacia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:38:10 by signacia          #+#    #+#             */
/*   Updated: 2021/11/15 19:57:01 by signacia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <sys/stat.h>

# define IS_PIPE						1
# define TOKEN_OR						2
# define TOKEN_REDIRECT_OUTPUT			3
# define TOKEN_REDIRECT_OUTPUT_APPEND	4
# define TOKEN_REDIRECT_INPUT			5
# define TOKEN_HEREDOC					6
# define TOKEN_AND						7
# define WILDCARD_ASTERISK				8

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
	struct s_envp	*prev;
}	t_envp;

typedef struct s_prog
{
	int				argc;
	char			**argv;
	int				is_argv;
	int				token;
	char			*output_file;
	int				fd_output_file;
	char			*input_file;
	int				fd_input_file;
	char			*heredoc;
	int				fd[2];
	int				fd_heredoc[2];
	int				do_not_launch;
	struct s_prog	*head;
	struct s_prog	*next;
}	t_prog;

typedef struct s_shell
{
	char	*input;
	int		child_exit_status;
	int		fd0_source;
	int		fd1_source;
	int		fd2_source;
	int		launch_method;
	t_prog	*apps;
	t_envp	*environment;
	int		argc;
	char	**argv;
}			t_shell;

typedef struct s_aster
{
	DIR				*dir;
	struct dirent	*cmp;
	int				k;
	int				j;
	int				argc;
}					t_aster;

typedef struct s_temp
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
}			t_temp;

void	add_application(t_shell *minishell);
int		dollar_handler(t_shell *minishell, int *i);
int		single_quote(t_shell *minishell, int *i);
int		double_quote(t_shell *minishell, int *i);
void	expand_argv(t_shell *minishell, int *i);
int		split_input(t_shell *minishell, int *i);
void	split_into_asterisk(t_shell *minishell, int *i);
t_aster	create_astr(void);
char	**lonely_pattern(char *pattern, t_aster	*astr);
int		tokens_handler(t_shell *minishell, int *i);
int		handle_or(t_shell *minishell, int *i);
int		heredoc(t_shell *minishell, int *i);
int		single_ampersand(t_shell *minishell, int *i);
int		double_ampersand(t_shell *minishell, int *i);
int		wildcards_handler(t_shell *minishell, int *i);
int		minishell_pre_executor(t_shell *minishell);
int		minishell_post_executor(t_shell *minishell);
void	minishell_scheduler(t_shell *minishell);
char	*get_prog_name(t_shell *minishell);
void	garbage_collector(t_shell *minishell);
int		syntax_error(t_shell *minishell, const char *token, int len);
int		runtime_error(t_shell *minishell, char *arg_name);
int		standard_error(t_shell *minishell, char *arg_name);
int		executing_error(t_shell *minishell);
int		pid_error(t_shell *minishell);
int		builtin_exec(t_shell *minishell);
void	computing_exit_status(t_shell *minishell);
void	heredoc_free(t_shell *minishell);

void	get_environment(t_shell *minishell, char **env);
int		get_pwd(t_shell *minishell, char **str);
int		get_echo(t_shell *minishell, char **args);
int		echo_check_flag(char *str);
void	write_echo(char **args, int i, int n);
int		get_cd(t_shell *minishell, char **str);
int		get_env(t_shell *minishell, char **str);
char	*find_pwd(t_shell *minishell, char *str);
void	change_old_new_pwd(t_shell *minishell, char *str, char *key);
int		get_export(t_shell *minishell, char **str);
int		sort_export(t_envp **tmp_env);
int		check_export(t_shell *minishell, char **str);
int		check_export_dup(t_envp *env, char **arr);
t_envp	*fullfill_env(t_envp *env);
void	ft_lst_swap_01(t_envp **swap);
void	ft_lst_swap_02(t_envp **swap);
void	ft_lst_swap_03(t_envp **swap);
int		get_unset(t_shell *minishell, char **str);
void	unset_del_elem(t_envp *tmp_exp, char *str, int f);
int		get_exit(t_shell *minishell, char **str);
int		get_exec(t_shell *minishell, char **str);
char	*ft_getenv_value(t_envp *lst, char *key);
void	cntrl_c(int sig);
void	cntrl_c2(int sig);
void	ft_lstadd_back_minishell(t_envp **lst, t_envp *new);
void	ft_lstclear_minishell(t_envp **lst);
t_envp	*ft_lstlast_minishell(t_envp *lst);
t_envp	*ft_lstnew_minishell(char *key, char *value);
int		ft_lstsize(t_envp *lst);
t_envp	*ft_lstfirst_minishell(t_envp *lst);
void	ft_lstdelone_minishell(t_envp *lst);
int		ft_error_cd(t_shell *minishell);
int		ft_error_cd_not_set(t_shell *minishell, char *str);
int		ft_error_cd_no_file(t_shell *minishell, char *str);
int		ft_error_export(t_shell *minishell, char *str);
int		ft_error_unset(t_shell *minishell, char *str);
void	check_list(t_envp *list);
char	**get_arr_env(t_envp *env);
void	base_signal(void);
void	input_eof(void);
void	check_shlvl(t_shell *minishell);
char	**ft_split_once(char *str, char ch);

#endif
