EXEC		=	minishell

CC			=	gcc
RM			=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

LIBFT		=	lib/libft/libft.a

GNL			=	lib/gnl/get_next_line.c

SRCS		=	./src/main.c\
				./src/utils/utils.c\
				./src/utils/utils_split.c\
				./src/lexer/tokenisateur.c\
				./src/lexer/help_parsor.c\
				./src/lexer/lexer_token.c\
				./src/lexer/parsor.c\
				./src/exec/exec.c\
				./src/built_in/cd.c\
				./src/built_in/env.c\
				./src/built_in/echo.c\
				./src/built_in/unset_pwd.c\
				./src/built_in/export.c\


OBJS		=	$(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(GNL) $(LIBFT) -o $(EXEC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

.PHONY: all clean fclean re