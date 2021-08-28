NAME   :=	minishell
SRC    :=	minishell.c signal_handler.c single_quote.c
OBJ    :=	$(SRC:.c=.o)
HDR    :=	minishell.h
CC     :=	gcc
CFLAGS :=	-Wall -Wextra -Werror -MMD
VPATH  :=	src include

all:		$(NAME)

# -lreadline - readline, add_history
# -ltermcap - tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
$(NAME):	$(OBJ)
			$(MAKE) -C libft
			$(CC) $(CFLAGS) -Llibft -lft -lreadline -L/Users/signacia/.brew/Cellar/readline/8.1/lib/ -ltermcap $(OBJ) -o $(NAME)

bonus:

%.o: %.c
			$(CC) $(CFLAGS) -Iinclude -Ilibft -I/Users/signacia/.brew/Cellar/readline/8.1/include -c $< -o $@

include		$(wildcard *.d)

test:		test.c
			${CC} ${CFLAGS} test.c

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
