SRCS = parsing/parsing.c

OBJS = ${SRCS:.c=.o}

INCLUDES = includes/cub.h get_next_line/get_next_line.h

NAME = cub3d

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

${NAME}: ${OBJS}
		${MAKE} -C ./libft
		cp libft/libft.a ${NAME}

all:	${NAME}

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean:	clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re:	fclean all

