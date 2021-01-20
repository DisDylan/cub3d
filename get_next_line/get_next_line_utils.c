/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:12:33 by dpoinsu           #+#    #+#             */
/*   Updated: 2020/12/01 14:33:56 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	size_t i;

	i = 0;
	if (!str)
		return (NULL);
	if (c == 0)
		return ((char*)str + ft_strlen(str));
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
