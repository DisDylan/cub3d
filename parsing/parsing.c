/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:31:43 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/20 16:23:44 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_params	init(t_struct params)
{
	params.res_high = 0;
	params.res_len = 0;
	params.north_path = NULL;
	params.south_path = NULL;
	params.west_path = NULL;
	params.east_path = NULL;
	params.ceil_r = -1;
	params.ceil_g = -1;
	params.ceil_b = -1;
	params.floor_r = -1;
	params.floor_g = -1;
	params.floor_b = -1;
	params.sprite_path = NULL;
	params.start_map = -1;
	params.header_error = 0;
	params.map_error = 0;
	params.map == NULL;
}	

void		parsing(char *path_fd)
{
	char **liste;
	char *str;
	int nb_lines;
	int fd;
	int i;
	t_params params;

	i = 0;
	fd = open(path_fd, O_RDONLY);
	init(params);
	while (get_next_line(fd, &str) == 1)
	{
		if (params.start_map == 1)
			params = get_map_line(str, params);
		else
		{
			params = treat_info(str, params);
			if (params.header_error == 1)
				return (header_error_message());
		}
	}
}

t_params	get_map_line(char *str, t_params params)
{

}

void		header_error_message(void)
{
	write(1, "Une erreur à été rencontré dans les paramètres !\n", 49);
}

t_params	treat_info(char *str, t_params params)
{
	if (str[0] == '\n')
		return (params);
	else if (str[0] == 'R')
		return (get_res(str, params));
	else if (str[0] == 'N' && str[1] == 'O')
		return (get_no_path(str, params));
	else if (str[0] == 'S' && str[1] == 'O')
		return (get_so_path(str, params));
	else if (str[0] == 'W' && str[1] == 'E')
		return (get_we_path(str, params));
	else if (str[0] == 'E' && str[1] == 'A')
		return (get_ea_path(str, params));
	else if (str[0] == 'S')
		return (get_sprite(str, params));
	else if (str[0] == 'F')
		return (get_floor_rgb(str, params));
	else if (str[0] == 'C')
		return (get_ceil_rgb(str, params));
	else if (ft_memchr((void)str, '1', ft_strlen(str)))
	{
		params.map[0] = ft_strdup(str);
		return (params.start_map = 1);
	}
	return (params.header_error = 1);
}
