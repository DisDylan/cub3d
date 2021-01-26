/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/26 11:51:11 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

typedef struct	s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}		t_data;

typedef struct	s_vars
{
	void *mlx;
	void *win;
}		t_vars;
/*
int	key_hook(t_vars *vars)
{
	printf("Hello from key_hook!\n");
	return (0);
}
*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	closing(t_vars *vars)
{ 
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int main(int argc, char **argv)
{
	char *path;
	int nb;
	//t_data img;
	t_vars vars;
	int x;
	int y;

	x = 5;
	y = 5;
	nb = argc;
	path = ft_strdup(argv[1]);
	printf("\n\n\n\n\n");
	parsing(path);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_hook(vars.win, 2, 1<<0, closing, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
