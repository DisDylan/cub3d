/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:31:43 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/25 12:05:02 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static t_params        print_linfo(char *str, t_params params)
{
        if (str[0] == '\n' || str[0] == '\0')
                return(params);
        else if (str[0] == 'R')
                printf("Résolution : %d & %d\n", params.res_high, params.res_len);
        else if (str[0] == 'N' && str[1] == 'O')
                printf("Nord : %s\n", params.north_path);
        else if (str[0] == 'S' && str[1] == 'O')
                printf("Sud : %s\n", params.south_path);
        else if (str[0] == 'W' && str[1] == 'E')
                printf("West : %s\n", params.west_path);
        else if (str[0] == 'E' && str[1] == 'A')
                printf("East : %s\n", params.east_path);
        else if (str[0] == 'S')
                printf("Item : %s\n", params.sprite_path);
        else if (str[0] == 'F')
                printf("Floor : %d & %d & %d\n", params.floor_r, params.floor_g, params.floor_b);
        else if (str[0] == 'C')
                printf("Ceil : %d & %d & %d\n", params.ceil_r, params.ceil_g, params.ceil_b);
        return (params);
}

t_params	init_params(void)
{
	t_params params;

	params.res_high = 0;
	params.res_len = 0;
	params.ceil_r = -1;
	params.ceil_g = -1;
	params.ceil_b = -1;
	params.floor_r = -1;
	params.floor_g = -1;
	params.floor_b = -1;
	params.start_map = -1;
	params.north_path = NULL;
	params.south_path = NULL;
	params.west_path = NULL;
	params.east_path = NULL;
	params.sprite_path = NULL;
	params.header_error = NULL;
	params.map_error = 0;
	return (params);
}	

void		parsing(char *path_fd)
{
	char *str;
	int fd;
	int i;
	int line_map;
	t_params params;

	line_map = 1;
	fd = open(path_fd, O_RDONLY);
	params = init_params();
	while ((i = get_next_line(fd, &str)) == 1)
	{
		if (params.start_map == 0)
		{
			if (start_map(str))
			{
				 params = get_map(fd, str, params, path_fd, line_map);
				 break;
			}
			i = 0;
			while (params.map[i])
			{
				printf("Line map = %s\n", params.map[i]);
				i++;
			}
		}
		else
		{
			params = treat_info(str, params);
			params = print_linfo(str, params);
			if (params.header_error != NULL)
			{
				printf("%s\n", params.header_error);
				break;
			}
			line_map++;
		}
	}
	if (check_map(&params))
		printf("!!!!!!\nTOUT EST OK YOUPI\n!!!!!!!\n");
	else
		printf("%s\n", params.map_error);
}

t_params	treat_info(char *str, t_params params)
{
	if (str[0] == '\n' || str[0] == '\0')
		return(params);
	else if (str[0] == 'R')
		params = get_res(str, params);
	else if (str[0] == 'N' && str[1] == 'O')
		params.north_path = get_path(str + 2, &params);
	else if (str[0] == 'S' && str[1] == 'O')
		params.south_path = get_path(str + 2, &params);
	else if (str[0] == 'W' && str[1] == 'E')
		params.west_path = get_path(str + 2, &params);
	else if (str[0] == 'E' && str[1] == 'A')
		params.east_path = get_path(str + 2, &params);
	else if (str[0] == 'S')
		params.sprite_path = get_path(str + 1, &params);
	else if (str[0] == 'F')
		params = get_floor_rgb(str + 1, params);
	else if (str[0] == 'C')
		params = get_ceil_rgb(str + 1, params);
	else
		params.start_map = 0;
	return (params);
}
