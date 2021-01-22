/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:58:43 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/22 15:00:10 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

t_params	header_no_message(t_params params)
{
	params.header_error = ft_strdup("Erreur Texture\n");
	return (params);
}

size_t		path_len(char *str, size_t *i)
{
	size_t j;
	char *nstr;

	j = 0;
	nstr = NULL;
	while (str[j] != ' ' && str[j] != '\0')
	{
		j++;
		*i += 1;
	}
	return (j);
}

char		*get_path(char *str, t_params *params)
{
	size_t i;
	size_t j;
	char *path;

	i = 0;
	if (str[i] == ' ')
		i++;
	else
		*params = header_no_message(*params);
	j = i;
	if (!(path = malloc(sizeof(path) * path_len(str + i, &j))))
		*params = header_no_message(*params);
	ft_strlcpy(path, str + i, path_len(str + i, &i) + 1);
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			*params = header_no_message(*params);
		i++;
	}
	/*
	fd_check = open(path, O_RDONLY);
	if (errno == ENOENT)
		*params = header_no_message(*params);
	close(fd_check);
	*/
	return (path);
}
