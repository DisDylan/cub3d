/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/28 09:45:20 by dpoinsu          ###   ########.fr       */
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
	char **map;
}		t_vars;

void    my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
        char *dst;

        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
}

int	closing(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}
/*
int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_r(int rgb)
{
	return (rgb & (0xFF << 16));
}

int	get_g(int rgb)
{
	return (rgb & (0xFF << 8));
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}
*/
int	draw_rect(int x, int y, t_vars *vars, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 10)
	{
		while (j < 10)
		{
			if (color == 1)
				my_mlx_pixel_put(vars, y + i, x + j, 0x00FFFFFF);
			else
				my_mlx_pixel_put(vars, y + i, x + j, 0x00555555);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	draw_map(t_vars *vars)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (vars->map[i])
	{
		printf("%s\n\n&&\n", vars->map[i]);
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '0')
				draw_rect(i * 11, j * 11, vars, 1);
			else if (vars->map[i][j] == '1')
				draw_rect(i * 11, j * 11, vars, 2);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, 900, 600);
	if (keycode == ESCAPE)
		closing(vars);
	else if (keycode == SPACE)
		draw_map(vars);
	/*
	else if (keycode == ARROW_RIGHT)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_new_image(vars->mlx, 640, 480);
		vars->x += 10;
		draw_rect(vars->x, vars->y, 10, 10, vars);
	}
	else if (keycode == ARROW_DOWN)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		vars->img = mlx_new_image(vars->mlx, 640, 480);
		vars->y += 10;
		draw_rect(vars->x, vars->y, 10, 10, vars);
	}
	else if (keycode == ARROW_LEFT)
        {
                mlx_destroy_image(vars->mlx, vars->img);
                vars->img = mlx_new_image(vars->mlx, 640, 480);
		vars->x -= 10;
                draw_rect(vars->x, vars->y, 10, 10, vars);
        }
        else if (keycode == ARROW_UP)
        {
                mlx_destroy_image(vars->mlx, vars->img);
                vars->img = mlx_new_image(vars->mlx, 640, 480);
		vars->y -= 10;
                draw_rect(vars->x, vars->y, 10, 10, vars);
        }
	*/
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
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
	t_params params;
	int x;
	int y;
//	int rgb;

	x = 5;
	y = 5;
	nb = argc;
	path = ft_strdup(argv[1]);
	printf("\n\n\n\n\n");
	params = parsing(path);
	vars.map = params.map;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 900, 600, "Hello there");
	vars.img = mlx_new_image(vars.mlx, 900, 600);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
