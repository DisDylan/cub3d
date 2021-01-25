#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"

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
	int map_error;
	char **map;
}				t_params;

void		parsing(char *path_fd);
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

#endif
