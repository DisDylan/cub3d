SRCS = src/errors.c src/get_next_line_utils.c src/get_next_line.c src/init.c src/keys_draw.c src/parsing_color_resolution_texture.c src/parsing_map.c src/parsing_utils.c src/raycasting_init.c src/raycasting_move.c src/raycasting_utils.c src/raycasting.c src/save.c src/sprites.c src/rgb.c src/ft_isdigit.c src/ft_itoa.c src/main.c

OBJS = ${SRCS:.c=.o}

INCLUDES = includes/cub.h

LIBS = -Lmlx_linux -lmlx_Linux -lXext -lX11 -lm -lz

NAME = cub3d

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ${INCLUDES}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS}

all:	${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

test:
	${CC} ${CFLAGS} -o cub3d ${SRCS} ${LIBS}
	./cub3d map.cub

test2:
	${CC} ${CFLAGS} -o cub3d ${SRCS} ${LIBS}
