/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:12:33 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/21 15:49:29 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strgchr(const char *str, int c)
{
	size_t i;

	i = 0;
	if (!str)
		return (NULL);
	if (c == 0)
		return ((char*)str + ft_strglen(str));
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
