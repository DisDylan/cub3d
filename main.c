/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/21 15:26:46 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int main(int argc, char **argv)
{
	char *path;
	int nb;
	int fd;

	nb = argc;
	path = ft_strdup(argv[1]);
	printf("ok 1\n");
	fd = open(path, O_RDONLY);
	printf("ok 2\n");
	printf("%s\n", path);
	free(path);
	while ((nb = get_next_line(fd, &path)) > 0)
		printf("%s\n", path);
	printf("ok 3\n");
	parsing(path);
	return (0);
}
