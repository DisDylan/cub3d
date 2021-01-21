/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:50:15 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/21 15:35:04 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static char	*ft_strgchr(const char *str, int c)
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

static char			*ft_strndup(char *s, size_t len)
{
	char *nstr;

	if (!(nstr = (char*)malloc(sizeof(nstr) * (len + 1))))
		return (NULL);
	ft_strlcpy(nstr, s, len);
	nstr[len] = '\0';
	return (nstr);
}

static int			make_new_line(char **save, char **line, char *str)
{
	char			*tmp;

	if (str != NULL)
	{
		*line = ft_strndup(*save, str - *save);
		tmp = ft_strndup(str + 1, ft_strlen(str + 1));
		free(*save);
		*save = tmp;
		return (1);
	}
	if (*save != NULL)
	{
		*line = *save;
		*save = NULL;
	}
	else
		*line = ft_strndup("", 1);
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char	*save[256];
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	char		*str;
	int			len;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((str = ft_strgchr(save[fd], '\n')) == 0
			&& (len = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[len] = 0;
		if (save[fd] == NULL)
			tmp = ft_strndup(buffer, len);
		else
			tmp = ft_strjoin(save[fd], buffer);
		if (save[fd] != 0)
			free(save[fd]);
		save[fd] = tmp;
	}
	if (len < 0)
		return (-1);
	return (make_new_line(&save[fd], line, str));
}
