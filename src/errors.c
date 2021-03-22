/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 08:12:14 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/03/17 08:12:16 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_verify_errors(t_recup *recup)
{
	if (ft_murs(recup) == 1)
		ft_error(recup, "Map error\n");
	if (recup->depart == 'x')
		ft_error(recup, "NO PLAYER\n");
	if (recup->multijoueurs == 1)
		ft_error(recup, "MAP ERROR\n");
	if (recup->lignevide == 1)
		ft_error(recup, "MAP ERROR\n");
	if (recup->wrongcharmap == 2)
		ft_error(recup, "MAP ERROR\n");
}

void	ft_error2(t_recup *recup)
{
	if (recup->map)
		free(recup->map);
	if (recup->s.order)
		free(recup->s.order);
	if (recup->s.dist)
		free(recup->s.dist);
	if (recup->sxy)
		free(recup->sxy);
	if (recup->s.zbuffer)
		free(recup->s.zbuffer);
	ft_exit(recup);
}

void	ft_error(t_recup *recup, char *str)
{
	int i;

	i = -1;
	recup->indicateur3 = 1;
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	if (recup->no)
		free(recup->no);
	if (recup->so)
		free(recup->so);
	if (recup->we)
		free(recup->we);
	if (recup->ea)
		free(recup->ea);
	if (recup->sp)
		free(recup->sp);
	if (recup->map)
	{
		while (++i < recup->nblines)
			free(recup->map[i]);
	}
	ft_error2(recup);
}

int		ft_exit(t_recup *recup)
{
	if (recup->data.img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->data.img);
	if (recup->texture[0].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[0].img);
	if (recup->texture[1].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[1].img);
	if (recup->texture[2].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[2].img);
	if (recup->texture[3].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[3].img);
	if (recup->texture[4].img)
		mlx_destroy_image(recup->data.mlx_ptr, recup->texture[4].img);
	if (recup->data.mlx_win)
		mlx_destroy_window(recup->data.mlx_ptr, recup->data.mlx_win);
	exit(0);
}
