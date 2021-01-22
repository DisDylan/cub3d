/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:03:53 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/22 10:33:24 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_params        header_error_message(t_params params)
{
        if (params.header_error == NULL)
                params.header_error = ft_strdup("Erreur de résolution");
        return (params);
}

size_t		check_res(char *str, t_params *params, size_t j)
{
	size_t i;

	i = j;
	if (ft_isdigit(str[i + 1]))
	{
		if (params->res_high == 0)
		{
			params->res_high = ft_atoi(str + (i + 1));
			i += ft_strlen(ft_itoa(params->res_high));
		}
		else if (params->res_len == 0)
		{
			params->res_len = ft_atoi(str + (i + 1));
			i += ft_strlen(ft_itoa(params->res_len));
		}
		else if (str[i] != ' ')
		{
			if (params->header_error == NULL)
				params->header_error = ft_strdup("Erreur de résolution");
		}
	}
	return (i);
}

t_params        get_res(char *str, t_params params)
{
        size_t i;

        i = 1;
        while (str[i] == ' ')
        {
		i = check_res(str, &params, i);
		if (str[i + 1] != ' ' && str[i + 1] != '\0')
                        params = header_error_message(params);
                i++;
        }
        if (params.res_high == 0 || params.res_len == 0)
		params = header_error_message(params);
        return (params);
}

