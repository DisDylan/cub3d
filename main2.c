/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/02/11 10:13:33 by dpoinsu          ###   ########.fr       */
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
	int char_x;
	int char_y;
	double speed;
	double angle;
	double rot_speed;
	int res_len;
	int res_high;
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
	while (i < 20)
	{
		while (j < 20)
		{
			if (color == 0)
				my_mlx_pixel_put(vars, y + i, x + j, 0x00FFFFFF);
			else if (color == 1)
				my_mlx_pixel_put(vars, y + i, x + j, 0x00555555);
			else if (color == 2)
				my_mlx_pixel_put(vars, y + i, x + j, 0x000000FF);
			else if (color == 3)
				my_mlx_pixel_put(vars, y + i, x + j, 0x0000FF00);
			j++;
		}
		i++;
		j = 0;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	draw_line(int x, int drawstart, int drawend, t_vars *vars, int color)
{
	while (drawstart <= drawend)
	{
		my_mlx_pixel_put(vars, x, drawstart, color);
		drawstart++;
	}
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
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '0')
				draw_rect(i * 21, j * 21, vars, 0);
			else if (vars->map[i][j] == '1')
				draw_rect(i * 21, j * 21, vars, 1);
			else if (vars->map[i][j] == '2')
				draw_rect(i * 21, j * 21, vars, 2);
			else if (vars->map[i][j] != ' ')
				draw_rect(i * 21, j * 21, vars, 3);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

void	move_player(t_vars *vars, int move)
{
	double tmpx;
	double tmpy;
	char swap;

	printf("%d\n", (int)vars->char_x);
	tmpx = vars->char_x + (vars->speed * cos(vars->angle) * move);
	printf("%d\n", (int)tmpx);
	printf("%d\n", (int)vars->char_y); 
	if (vars->map[(int)(tmpx)][(int)(vars->char_y)] == '0')
	{
		vars->char_x = tmpx;
		swap = vars->map[vars->char_y][vars->char_x];
                vars->map[vars->char_y][vars->char_x] = vars->map[vars->char_y][vars->char_x + move];
                vars->map[vars->char_y][vars->char_x + move] = swap;
                vars->char_x += move;
	}
	tmpy = vars->char_x + (vars->speed * sin(vars->angle) * move);
        if (vars->map[(int)vars->char_x][(int)(tmpy)] == '0')
	{
                vars->char_y = tmpy;
		swap = vars->map[vars->char_y][vars->char_x];
                vars->map[vars->char_y][vars->char_x] = vars->map[vars->char_y + move][vars->char_x];
                vars->map[vars->char_y + move][vars->char_x] = swap;
                vars->char_y += move;
	}
}

void	move_player_y(t_vars *vars, int move)
{
	char swap;

	if (vars->map[vars->char_y + move][vars->char_x] == '0')
	{
		swap = vars->map[vars->char_y][vars->char_x];
		vars->map[vars->char_y][vars->char_x] = vars->map[vars->char_y + move][vars->char_x];
		vars->map[vars->char_y + move][vars->char_x] = swap;
		vars->char_y += move;
	}
}

void    move_player_x(t_vars *vars, int move)
{
        char swap;

        if (vars->map[vars->char_y][vars->char_x + move] == '0')
        {
                swap = vars->map[vars->char_y][vars->char_x];
                vars->map[vars->char_y][vars->char_x] = vars->map[vars->char_y][vars->char_x + move];
                vars->map[vars->char_y][vars->char_x + move] = swap;
		vars->char_x += move;
        }
}

void	draw_angle(t_vars *vars)
{
	int len;

	len = 0;
	while (len < 20)
	{
		//draw_rect((vars->res_len - 100) + len, (vars->res_high - 50) + len, vars, 0X00FF000000);
		my_mlx_pixel_put(vars, ((vars->res_len - 100) + len), ((vars->res_high - 50) + len), 0x00FF0000);
		len++;
		vars->angle += vars->rot_speed;
	}
}

int	key_hook(int keycode, t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, vars->res_len, vars->res_high);
	if (keycode == ESCAPE)
		closing(vars);
	else if (keycode == KEY_Z)
		move_player_y(vars, -1);
	else if (keycode == KEY_Q)
		move_player_x(vars, -1);
	else if (keycode == KEY_S)
		move_player_y(vars, 1);
	else if (keycode == KEY_D)
		move_player_x(vars, 1);
	else if (keycode == ARROW_LEFT)
		draw_angle(vars);
	else if (keycode == ARROW_RIGHT)
		vars->angle -= vars->rot_speed;
	draw_angle(vars);
	draw_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	print_key(int keycode)
{
	printf("Relache de la touche %d\n", keycode);
	return (0);
}

typedef struct s_ray
{
	double posx;
	double posy;
	double dirx;
	double diry;
	double planx;
	double plany;
	double raydirx;
	double raydiry;
	double camerax;
	int mapx;
	int mapy;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	int stepx;
	int stepy;
	int hit;
	int side;
	double perpwalldist;
	int lineheight;
	int drawstart;
	int drawend;
	int x;
}	t_ray;

int main(int argc, char **argv)
{
	char *path;
	int nb;
	t_vars vars;
	t_params params;
	t_ray raycast;
	int x;
	int y;
//	int rgb;

	x = 5;
	y = 5;
	nb = argc;
	path = ft_strdup(argv[1]);
	printf("\n\n\n\n\n");
	params = parsing(path);
	printf("ok après parse");
	vars.map = params.map;
	vars.speed = 1;
	vars.angle = 0;
	vars.rot_speed = 0.02;

	vars.res_high = params.res_len;
	vars.res_len = params.res_high;
	vars.char_x = params.player_x;
	vars.char_y = params.player_y;
	///////////////////////////////////////
	raycast.posx = (int)vars.char_x;
	raycast.posy = (int)vars.char_y;
	printf("coucou");
	raycast.dirx = params.dirx;
	raycast.diry = params.diry;
	/*if (params.dir == 'W')
	{
		raycast.dirx = 1;
		raycast.diry = 0;
	}
	else if (params.dir == 'N')
	{
		raycast.dirx = 0;
		raycast.diry = 1;
	}
	else if (params.dir == 'E')
	{
		raycast.dirx = -1;
		raycast.diry = 0;
	}
	else
	{
		raycast.dirx = 0;
		raycast.diry = -1;
	}*/
	printf("coucou");
	raycast.dirx = 1;
	raycast.diry = 0;
	printf("directions: %f & %f", raycast.dirx, raycast.diry);
	raycast.planx = 0;
	raycast.plany = 0.66;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.res_len, vars.res_high, "cub3d - dpoinsu");
	vars.img = mlx_new_image(vars.mlx, vars.res_len, vars.res_high);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	//draw_map(&vars);

	while (raycast.x < vars.res_len)
	{
		raycast.camerax = 2 * raycast.x / (double)vars.res_len - 1;
		raycast.raydirx = raycast.dirx + raycast.planx * raycast.camerax;
		raycast.raydiry = raycast.diry + raycast.plany * raycast.camerax;
		raycast.mapx = (int)raycast.posx;
		raycast.mapy = (int)raycast.posy;
		raycast.deltadistx = sqrt(1 + (raycast.raydiry * raycast.raydiry) / (raycast.raydirx * raycast.raydirx));
		raycast.deltadisty = sqrt(1 + (raycast.raydirx * raycast.raydirx) / (raycast.raydiry * raycast.raydiry));
		//raycast.deltadistx = fabs(1 / raycast.raydirx);
		//raycast.deltadisty = fabs(1 / raycast.raydiry);
		raycast.hit = 0;
		if (raycast.raydirx < 0)
		{
			raycast.stepx = -1;
			raycast.sidedistx = (raycast.posx - raycast.mapx) * raycast.deltadistx;
		}
		else
		{
			raycast.stepx = 1;
			raycast.sidedistx = (raycast.mapx + 1.0 - raycast.posx) * raycast.deltadistx;
		}
		if (raycast.raydiry < 0)
		{
			raycast.stepy = -1;
			raycast.sidedisty = (raycast.posy - raycast.mapy) * raycast.deltadisty;
		}
		else
		{
			raycast.stepy = 1;
			raycast.sidedisty = (raycast.mapy + 1.0 - raycast.posy) * raycast.deltadisty;
		}
		while (raycast.hit == 0)
		{
			if (raycast.sidedistx < raycast.sidedisty)
			{
				raycast.sidedistx += raycast.deltadistx;
				raycast.mapx += raycast.stepx;
				raycast.side = 0;
			}
			else
			{
				raycast.sidedisty += raycast.deltadisty;
				raycast.mapy += raycast.stepy;
				raycast.side = 1;
			}
			if (vars.map[raycast.mapx][raycast.mapy] != '0')
				raycast.hit = 1;
		}
		if (raycast.side == 0)
			raycast.perpwalldist = (raycast.mapx - raycast.posx + (1 - raycast.stepx) / 2) / raycast.raydirx;
		else
			raycast.perpwalldist = (raycast.mapy - raycast.posy + (1 - raycast.stepy) / 2) / raycast.raydiry;
		raycast.lineheight = (int)(vars.res_high / raycast.perpwalldist);
		raycast.drawstart = (raycast.lineheight * -1) / 2 + vars.res_high / 2;
		printf("drawstart: %d\n", raycast.drawstart);
		if (raycast.drawstart < 0 )
			raycast.drawstart = 0;
		raycast.drawend = raycast.lineheight / 2 + vars.res_high / 2;
		if (raycast.drawend >= vars.res_high)
			raycast.drawend = vars.res_high - 1;
		raycast.x += 1;
		int color;
		if (vars.map[raycast.mapx][raycast.mapy] == '1')
			color = 0x00555555;
		if (vars.map[raycast.mapx][raycast.mapy] == '2')
			color = 0x00FF0000;
		if (vars.map[raycast.mapx][raycast.mapy] == '0')
			color = 0x0000FFFF;
		if (raycast.side == 1)
			color = color / 2;
		draw_line(raycast.x, raycast.drawstart, raycast.drawend, &vars, color);
	}
	///////////////////////////////////////
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	//mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
