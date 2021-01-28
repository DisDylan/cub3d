/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 09:47:17 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/28 10:09:26 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
}		t_data;

int key_hook(int keycode)
{
	printf("keycode : %d\n", keycode);
	return (0);
}

int main(void)
{
	void *mlx;
	void *win;
	//t_data data;

	mlx = mlx_init();
	printf("1 ok\n");
	win = mlx_new_window(mlx, 1900, 1000, "coucou");
	printf("2 ok\n");
//	data.img = mlx_new_image(mlx, 1900, 1000);
//	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
//	mlx_key_hook(win, key_hook, &data);
	mlx_loop(mlx);
	return (0);
}
