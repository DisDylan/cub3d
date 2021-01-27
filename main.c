/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/27 11:07:50 by dpoinsu          ###   ########.fr       */
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
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	void *mlx;
	void *win;
	int x;
	int y;
}		t_vars;

void    my_mlx_pixel_put(t_vars *data, int color)
{
        char *dst;

        dst = data->addr + (data->y * data->line_length + data->x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        data->x += 1;
        data->y += 1;
	printf("x = %d\n", data->x);
	printf("y = %d\n", data->y);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == SPACE)
	{
		my_mlx_pixel_put(vars, 0x00FF0000);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	else if (keycode == ROT_LEFT)
		printf("Tourne à gauche\n");
	else if (keycode == ROT_RIGHT)
		printf("Tourne à droite\n");
	else if (keycode == KEY_Z)
		printf("DROIIIITTT DEVAAANNNTTT\n");
	else if (keycode == KEY_S)
		printf("Reculer pour mieux sauter\n");
	else if (keycode == KEY_Q)
		printf("Déplacement à gauche\n");
	else if (keycode == KEY_D)
		printf("Déplacement à droite\n");
	return (0);
}

int	closing(t_vars *vars)
{ 
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	print_key(int keycode)
{
	printf("Relache de la touche %d\n", keycode);
	return (0);
}

int main(int argc, char **argv)
{
	char *path;
	int nb;
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
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello there");
	vars.img = mlx_new_image(vars.mlx, 640, 480);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
//	mlx_hook(vars.win, 3, 1L<<2, mlx_key_hook(vars.win, key_hook, &vars), &vars);
	mlx_loop(vars.mlx);
	return (0);
}
