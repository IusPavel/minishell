NAME   :=	minishell
SRC    :=	minishell.c quotes_handler.c dollar_handler.c \
			split_into_mandatory.c exec_apps.c exec_u_apps.c \
			garbage_collector.c tokens_handler.c tokens_her_bonus.c \
			builtin_errors.c app_handler.c wildcards_handler.c utils.c \
			minishell_exit.c minishell_unset.c minishell_export_u.c \
			minishell_export.c minishell_cd.c minishell_cd_u.c \
			minishell_echo.c errors_handler.c minishell_pwd.c lst_functions.c \
			minishell_env.c shlvl_handler.c minishell_signals.c \
			split_into_asterisk.c split_into_asterisk_u.c ft_split_once.c

OBJ    :=	$(SRC:.c=.o)
HDR    :=	minishell.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD
VPATH  :=	src include

all:		$(NAME)

$(NAME):	$(OBJ)
			$(MAKE) -C libft
			$(CC) $(CFLAGS) -Llibft -lft -lreadline -L/Users/${USER}/.brew/Cellar/readline/8.1/lib/ -ltermcap $(OBJ) -o $(NAME)

bonus:

%.o: %.c
			$(CC) $(CFLAGS) -Iinclude -Ilibft -I/Users/${USER}/.brew/Cellar/readline/8.1/include -c $< -o $@

include		$(wildcard *.d)

test:
			$(CC) $(CFLAGS) -o test test.c -lreadline

readline:
			brew install readline

readline_uninstall:
			brew uninstall readline

clean:
			rm -rf *.o *.d
			$(MAKE) clean -C libft

fclean:		clean
			rm -rf $(NAME)
			$(MAKE) fclean -C libft

re:			fclean all

.PHONY:		all clean fclean re bonus readline readline_uninstall
