/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:33:25 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/03/22 14:33:45 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int		put_int_r(char *str, int *i, int *comma, t_recup *recup)
{
	int g;

	g = -1;
	while (str[*i] && *comma < 2)
	{
		if (str[*i] == ' ')
			*i += 1;
		else if (str[*i] == ',')
		{
			*comma += 1;
			*i += 1;
		}
		else if (ft_isdigit(str[*i]) && g < 0)
		{
			g = ft_atoi(str + *i);
			*i += ft_strlen(ft_itoa(g));
		}
		else
		{
		    recup->indicateur2 = 1;
			break;
		}
	}
	return(g);
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

int		put_int_rgb(char *str, t_recup *recup)
{
	int i;
    int r;
    int g;
    int b;
	int comma;

	i = 1;
	b = -1;
    while (str[i] == ' ')
        i++;
	comma = 0;
	r = ft_atoi(str + i);
	i += ft_strlen(ft_itoa(r));
	g = put_int_r(str, &i, &comma, recup);
	while (str[i] == ' ')
		i++;
	if (comma == 2 && r != -1 && g != -1)
	{
		b = ft_atoi(str + i);
		i += ft_strlen(ft_itoa(b));
	}
	else
		recup->indicateur2 = 1;
	check_rgb_end_line(str, i, recup);
    return(trgb(0, r, g, b));
}