/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 09:21:05 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/02/11 12:33:03 by dpoinsu          ###   ########.fr       */
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

typedef struct	s_vars
{
	void *img;
	int *addr;
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
	t_ray raycast;
}		t_vars;

void    my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
    int *dst;

	printf("ok!!\n");
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	printf("ok!!\n");
	dst[0] = color;
	printf("ok!!!\n");
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

void draw_screen(t_vars *vars)
{
	while (vars->raycast.x < vars->res_len)
	{
		vars->raycast.camerax = 2 * vars->raycast.x / (double)vars->res_len - 1;
		vars->raycast.raydirx = vars->raycast.dirx + vars->raycast.planx * vars->raycast.camerax;
		vars->raycast.raydiry = vars->raycast.diry + vars->raycast.plany * vars->raycast.camerax;
		vars->raycast.mapx = (int)vars->raycast.posx;
		vars->raycast.mapy = (int)vars->raycast.posy;
		vars->raycast.deltadistx = sqrt(1 + (vars->raycast.raydiry * vars->raycast.raydiry) / (vars->raycast.raydirx * vars->raycast.raydirx));
		vars->raycast.deltadisty = sqrt(1 + (vars->raycast.raydirx * vars->raycast.raydirx) / (vars->raycast.raydiry * vars->raycast.raydiry));
		//vars->raycast.deltadistx = fabs(1 / vars->raycast.raydirx);
		//vars->raycast.deltadisty = fabs(1 / vars->raycast.raydiry);
		vars->raycast.hit = 0;
		if (vars->raycast.raydirx < 0)
		{
			vars->raycast.stepx = -1;
			vars->raycast.sidedistx = (vars->raycast.posx - vars->raycast.mapx) * vars->raycast.deltadistx;
		}
		else
		{
			vars->raycast.stepx = 1;
			vars->raycast.sidedistx = (vars->raycast.mapx + 1.0 - vars->raycast.posx) * vars->raycast.deltadistx;
		}
		if (vars->raycast.raydiry < 0)
		{
			vars->raycast.stepy = -1;
			vars->raycast.sidedisty = (vars->raycast.posy - vars->raycast.mapy) * vars->raycast.deltadisty;
		}
		else
		{
			vars->raycast.stepy = 1;
			vars->raycast.sidedisty = (vars->raycast.mapy + 1.0 - vars->raycast.posy) * vars->raycast.deltadisty;
		}
		while (vars->raycast.hit == 0)
		{
			if (vars->raycast.sidedistx < vars->raycast.sidedisty)
			{
				vars->raycast.sidedistx += vars->raycast.deltadistx;
				vars->raycast.mapx += vars->raycast.stepx;
				vars->raycast.side = 0;
			}
			else
			{
				vars->raycast.sidedisty += vars->raycast.deltadisty;
				vars->raycast.mapy += vars->raycast.stepy;
				vars->raycast.side = 1;
			}
			if (vars->map[vars->raycast.mapx][vars->raycast.mapy] != '0')
				vars->raycast.hit = 1;
		}
		if (vars->raycast.side == 0)
			vars->raycast.perpwalldist = (vars->raycast.mapx - vars->raycast.posx + (1 - vars->raycast.stepx) / 2) / vars->raycast.raydirx;
		else
			vars->raycast.perpwalldist = (vars->raycast.mapy - vars->raycast.posy + (1 - vars->raycast.stepy) / 2) / vars->raycast.raydiry;
		vars->raycast.lineheight = (int)(vars->res_high / vars->raycast.perpwalldist);
		vars->raycast.drawstart = (vars->raycast.lineheight * -1) / 2 + vars->res_high / 2;
		if (vars->raycast.drawstart < 0 )
			vars->raycast.drawstart = 0;
		vars->raycast.drawend = vars->raycast.lineheight / 2 + vars->res_high / 2;
		if (vars->raycast.drawend >= vars->res_high)
			vars->raycast.drawend = vars->res_high - 1;
		vars->raycast.x += 1;
		int color;
		if (vars->map[vars->raycast.mapx][vars->raycast.mapy] == '1')
			color = 0x00555555;
		if (vars->map[vars->raycast.mapx][vars->raycast.mapy] == '2')
			color = 0x00FF0000;
		if (vars->map[vars->raycast.mapx][vars->raycast.mapy] == '0')
			color = 0x0000FFFF;
		if (vars->raycast.side == 1)
			color = color / 2;
		draw_line(vars->raycast.x, vars->raycast.drawstart, vars->raycast.drawend, vars, color);

	}
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
	params = parsing(path);
	vars.map = params.map;
	vars.speed = 1;
	vars.angle = 0;
	vars.rot_speed = 0.02;

	vars.res_high = params.res_len;
	vars.res_len = params.res_high;
	vars.char_x = params.player_x;
	vars.char_y = params.player_y;
	///////////////////////////////////////
	vars.raycast.posx = (int)vars.char_x;
	vars.raycast.posy = (int)vars.char_y;
	vars.raycast.dirx = 1;
	vars.raycast.diry = 0;
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
	vars.raycast.planx = 0;
	vars.raycast.plany = 0.66;
	draw_screen(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.res_len, vars.res_high, "cub3d - dpoinsu");
	vars.img = mlx_new_image(vars.mlx, vars.res_len, vars.res_high);
	vars.addr = (int *)mlx_get_data_addr(vars.img, &vars.bits_per_pixel, &vars.line_length, &vars.endian);
	//draw_map(&vars);
	///////////////////////////////////////
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
