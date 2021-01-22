/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:31:43 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/22 10:11:19 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
	params.header_error = NULL;
	params.map_error = 0;
	return (params);
}	

void		parsing(char *path_fd)
{
	char *str;
	int fd;
	int i;
	t_params params;

	fd = open(path_fd, O_RDONLY);
	params = init_params();
	while ((i = get_next_line(fd, &str)) == 1)
	{
		if (params.start_map == 1)
			break;
		else
		{
			params = treat_info(str, params);
			if (params.header_error != NULL)
			{
				printf("%s\n", params.header_error);
				break;
			}
		}
	}
}

t_params	treat_info(char *str, t_params params)
{
	if (str[0] == '\n' || str[0] == '\0')
		return(params);
	else if (str[0] == 'R')
	{
		params = get_res(str, params);
		printf("%d et %d (HIGH & LEN)\n", params.res_high, params.res_len);
	}
	else if (str[0] == 'N' && str[1] == 'O')
		printf("NO path\n");
	else if (str[0] == 'S' && str[1] == 'O')
		printf("SO path\n");
	else if (str[0] == 'W' && str[1] == 'E')
		printf("WE path\n");
	else if (str[0] == 'E' && str[1] == 'A')
		printf("EA path\n");
	else if (str[0] == 'S')
		printf("Sprite\n");
	else if (str[0] == 'F')
		printf("Floor\n");
	else if (str[0] == 'C')
		printf("Ceil\n");
	/*else if (ft_memchr((void)str, '1', ft_strlen(str)))
	{
		params.map[0] = ft_strdup(str);
		return (params.start_map = 1);
	}*/
	return (params);
}
