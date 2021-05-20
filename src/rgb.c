/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:33:25 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/05/20 10:29:16 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		put_int_r(char *str, int *i, t_recup *recup)
{
	int g;

	g = -1;
	while (str[*i] && recup->comma < 2)
	{
		if (str[*i] == ' ')
			*i += 1;
		else if (str[*i] == ',')
		{
			recup->comma += 1;
			*i += 1;
		}
		else if (ft_isdigit(str[*i]) && g < 0)
		{
			g = ft_atoi(str + *i);
			*i += nblen(g);
		}
		else
		{
			recup->indicateur2 = 1;
			break ;
		}
	}
	return (g);
}

void	check_rgb_end_line(char *str, int i, t_recup *recup)
{
	while (str[i])
	{
		if (str[i] != ' ')
			recup->indicateur2 = 1;
		i++;
	}
}

void	check_min_max(int r, int g, int b, t_recup *recup)
{
	if (r > 255 || g > 255 || b > 255)
		recup->indicateur2 = 1;
	if (r < 0 || g < 0 || b < 0)
		recup->indicateur2 = 1;
}

int		put_int_rgb(char *str, t_recup *recup)
{
	int i;
	int r;
	int g;
	int b;

	i = 1;
	b = -1;
	while (str[i] == ' ')
		i++;
	recup->comma = 0;
	r = ft_atoi(str + i);
	i += nblen(r);
	g = put_int_r(str, &i, recup);
	while (str[i] == ' ')
		i++;
	if (recup->comma == 2 && r != -1 && g != -1)
	{
		b = ft_atoi(str + i);
		i += nblen(b);
	}
	else
		recup->indicateur2 = 1;
	check_min_max(r, g, b, recup);
	check_rgb_end_line(str, i, recup);
	return (trgb(0, r, g, b));
}
