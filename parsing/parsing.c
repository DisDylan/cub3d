/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:31:43 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/21 15:19:13 by dpoinsu          ###   ########.fr       */
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
	params.header_error = 0;
	params.map_error = 0;
	return (params);
}	

void		parsing(char *path_fd)
{
	char *str;
	int fd;
	t_params params;

	printf("ok");
	fd = open(path_fd, O_RDONLY);
	printf("ok");
	params = init_params();
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

	printf("ok\n");
	printf("%s\n", str);
	return (params);
}

void		header_error_message(void)
{
	write(1, "Une erreur à été rencontré dans les paramètres !\n", 49);
}

t_params	treat_info(char *str, t_params params)
{
	if (str[0] == '\n')
		printf("Ligne vide\n");
	else if (str[0] == 'R')
		printf("Résolution\n");
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
