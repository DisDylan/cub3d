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
	char sprite_path;
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

#endif
