NAME   =	libft.a

SRCS   =	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strjoin_free.c ft_putchar.c ft_putendl.c ft_putnbr.c ft_putstr.c \
			ft_strcpy.c  ft_strcmp.c

SRCS_B =	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c

OBJS   =	$(SRCS:.c=.o)

OBJS_B =	$(SRCS_B:.c=.o)

HDR    =	libft.h

CC     =	gcc

CFLAGS =	-Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -c $^ -o $@

all:		$(NAME)

$(NAME):	$(OBJS) $(HDR)
			ar -crs $(NAME) $?

bonus:		$(OBJS_B) $(HDR)
			ar -crs $(NAME) $?

clean:
			rm -rf *.o

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus
