/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/22 14:37:38 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

int main(int argc, char **argv)
{
	char *path;
	int nb;

	nb = argc;
	path = ft_strdup(argv[1]);
	printf("\n\n\n\n\n");
	parsing(path);
	return (0);
}
