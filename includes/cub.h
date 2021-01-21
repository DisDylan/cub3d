#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

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
	int sprite_path;
	int start_map;
	int header_error;
	int map_error;
	char **map;
}				t_params;

int			get_next_line(int fd, char **line);
void		parsing(char *path_fd);
t_params	get_map_line(char *str, t_params params);
void		header_error_message(void);
t_params	treat_info(char *str, t_params params);

#endif
