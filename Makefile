SRCS = parsing/parsing.c get_next_line/get_next_line.c

OBJS = ${SRCS:.c=.o}

INCLUDES = includes/cub.h

NAME = cub3d

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

${NAME}: ${OBJS}
		${MAKE} -C ./libft
		cp libft/libft.a .

all:	
	${CC} ${CFLAGS} parsing/parsing.c get_next_line/get_next_line.c -L. -lft

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean:	clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re:	fclean all

