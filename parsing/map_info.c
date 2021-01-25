/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 14:00:55 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/25 09:53:20 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int		start_map(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == '0' ||
				str[i] != '2')
			return (1);
		i++;
	}
	return (0);
}

t_params	get_map(int fd, char *str, t_params params, char *path, int line_map)
{
	int i;
	int nb_lines;
	int size_map;
	
	i = 0;
	nb_lines = 1;
	size_map = 1;
	while ((i = get_next_line(fd, &str)) == 1)
		size_map++;
	// début map ligne 12;
	// tant qu'on read, nb_line ++;
	close(fd);
	// close
	// malloc
	params.map = malloc(sizeof(params.map) * size_map + 2);
	// open
	fd = open(path, O_RDONLY);
	// tant qu'on est pas à 12, ++;
	while (nb_lines != line_map)
	{
		i = get_next_line(fd, &str);
		nb_lines++;
	}
	i = 1;
	params.map[0] = ft_strdup(str);
	while ((size_map = get_next_line(fd, &str)) == 1)
	{
		params.map[i] = ft_strdup(str);
		i++;
	}
	close(fd);
	return (params);
}
