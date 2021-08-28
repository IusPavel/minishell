#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h> // signal
# include <term.h> // tgetent
# include <termios.h> // tcgetattr, tcsetattr

typedef struct s_shell
{
	char	*input; // считанная строка
	char	**envp;	// env


// 		junk
	int		argc;
	char	**argv;
}			t_shell;
//void	sighandler(int sig);
char	*single_quote(char *input, int *i);
char	*double_quote(char *input, int *i, char **envp);
char	*dollar(char *input, int *i, char **envp);
#endif