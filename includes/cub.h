#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../mlx_linux/mlx.h"

# define KEY_Z 122
# define KEY_Q 113
# define KEY_S 115
# define KEY_D 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define ARROW_DOWN 65364
# define ARROW_UP 65362
# define ESCAPE 65307
# define SPACE 32

typedef struct	s_params
{
	int res_high;
	int res_len;
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
	int ceil_r;
	int ceil_g;
	int ceil_b;
	int floor_r;
	int floor_g;
	int floor_b;
	char *sprite_path;
	int start_map;
	char *header_error;
	char *map_error;
	char **map;
	int player_x;
	int player_y;
	int dirx;
	int diry;
}				t_params;

t_params	parsing(char *path_fd);
t_params	header_error_message(t_params params);
t_params	treat_info(char *str, t_params params);
t_params        get_res(char *str, t_params params);
size_t		check_res(char *str, t_params *params, size_t j);
t_params	header_no_message(t_params params);
size_t		path_len(char *str, size_t *i);
char		*get_path(char *str, t_params *params);
t_params        get_ceil_rgb(char *str, t_params);
t_params        get_floor_rgb(char *str, t_params);
void            put_int_rgb(int *r, int *g, int *b, char *str, t_params *params);
t_params        error_rgb(t_params params);
t_params        get_map(int fd, char *str, t_params params, char *path, int line_map);
int             start_map(char *str);
int             check_map(t_params *params);
void            check_line(char **tab, int i, t_params *params);
void            check_item(char c, t_params *params);
void            check_first_line(char *line, t_params *params);

#endif
