/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:03:50 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/22 16:25:14 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_params	error_rgb(t_params params)
{
	if (params.header_error == NULL)
		params.header_error = ft_strdup("Erreur de RGB\n");
	return (params);
}

void		put_int_rgb(int *r, int *g, int *b, char *str, t_params *params)
{
	size_t i;
	int comma;

	i = 0;
	comma = 0;
	*r = ft_atoi(str);
	i += ft_strlen(ft_itoa(*r));
	while (str[i] && comma < 2)
	{	
		if (str[i] == ' ')
			i++;
		else if (str[i] == ',')
		{
			comma += 1;
			i++;
		}
		else if (ft_isdigit(str[i]) && *g < 0)
		{
			*g = ft_atoi(str + i);
			i += ft_strlen(ft_itoa(*g));
		}
		else
		{
			*params = error_rgb(*params);
			break;
		}
	}
	while (str[i] == ' ')
		i++;
	if (comma == 2 && r != 0 && g != 0)
	{
		*b = ft_atoi(str + i);
		i += ft_strlen(ft_itoa(*b));
	}
	else
		*params = error_rgb(*params);
	while (str[i])
	{
		if (str[i] != ' ')
			*params = error_rgb(*params);
		i++;
	}
}

t_params	get_floor_rgb(char *str, t_params params)
{
	int i;
	
	i = 0;
	if (str[i] != ' ')
		params = error_rgb(params);
	while (str[i] == ' ')
		i++;
	put_int_rgb(&params.floor_r, &params.floor_g, &params.floor_b, str + i, &params);
	if (params.floor_r < 0 || params.floor_g < 0 || params.floor_b < 0 ||
                        params.floor_r > 255 || params.floor_g > 255 || params.floor_b > 255)
                params = error_rgb(params);
	return (params);
}

t_params        get_ceil_rgb(char *str, t_params params)
{
        int i;

        i = 0;
	if (str[i] != ' ')
		params = error_rgb(params);
        while (str[i] == ' ')
                i++;
        put_int_rgb(&params.ceil_r, &params.ceil_g, &params.ceil_b, str + i, &params);
	if (params.ceil_r < 0 || params.ceil_g < 0 || params.ceil_b < 0 ||
			params.ceil_r > 255 || params.ceil_g > 255 || params.ceil_b > 255)
		params = error_rgb(params);
        return (params);
}

