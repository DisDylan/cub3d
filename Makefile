SRCS = parsing/*.c get_next_line/*.c main2.c

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
	${CC} ${CFLAGS} parsing/*.c get_next_line/*.c main.c -L. -lft

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean:	clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}

re:	fclean all

test:
	${CC} ${CFLAGS} -o cub3d ${SRCS} -L. -lft -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz
	./cub3d map/map.cub
