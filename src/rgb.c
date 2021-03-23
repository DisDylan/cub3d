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

int		put_int_rgb(char *str, t_recup *recup)
{
	int i;
    int r;
    int g;
    int b;
	int comma;

	i = 1;
    while (str[i] == ' ')
        i++;
	comma = 0;
	r = ft_atoi(str);
	i += ft_strlen(ft_itoa(r));
	while (str[i] && comma < 2)
	{	
		if (str[i] == ' ')
			i++;
		else if (str[i] == ',')
		{
			comma += 1;
			i++;
		}
		else if (ft_isdigit(str[i]) && g < 0)
		{
			g = ft_atoi(str + i);
			i += ft_strlen(ft_itoa(g));
		}
		else
		{
		    recup->indicateur2 = 1;
			break;
		}
	}
	while (str[i] == ' ')
		i++;
	if (comma == 2 && r != 0 && g != 0)
	{
		b = ft_atoi(str + i);
		i += ft_strlen(ft_itoa(b));
	}
	else
		recup->indicateur2 = 1;
	while (str[i])
	{
		if (str[i] != ' ')
		    recup->indicateur2 = 1;
		i++;
	}
    return(trgb(0, r, g, b));
}

int get_rgb(char *str, t_recup *recup)
{
    int i;
    int rgb;

    i = 1;
    rgb = -1;
    if (str[0] == 'F')
        rgb = put_int_rgb(str, recup);
    else if (str[0] == 'C')
        rgb = put_int_rgb(str, recup);
    return(rgb);
}