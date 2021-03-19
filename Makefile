SRCS = src/*.c

OBJS = ${SRCS:.c=.o}

INCLUDES = includes/cub.h

NAME = cub3d

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

all:	
	${MAKE} -C ./libft
	${CC} ${CFLAGS} -o cub3d ${SRCS} -Llibft -lft -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz

${NAME}: ${OBJS}
		all

clean:
	${MAKE} clean -C ./libft
	${RM} ${OBJS}

fclean:	clean
	${MAKE} fclean -C ./libft
	${RM} ${NAME}
	${RM} libft.a

re:	fclean all

test:
	${CC} ${CFLAGS} -o cub3d ${SRCS} -L. -lft -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz
	./cub3d map.cub