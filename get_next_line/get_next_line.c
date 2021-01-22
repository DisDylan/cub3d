/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:50:15 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/21 15:49:42 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strglen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char			*ft_strncpy(char *dst, char *src, size_t n)
{
	size_t		i;

	if (dst == 0 && src == 0)
		return (dst);
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static char			*ft_strgjoin(char *s1, char *s2)
{
	char *nstr;

	if (!s1 && !s2)
		return (NULL);
	if (!(nstr = (char*)malloc(sizeof(nstr) *
					(ft_strglen(s1) + ft_strglen(s2) + 1))))
		return (NULL);
	ft_strncpy(nstr, s1, ft_strglen(s1));
	ft_strncpy(nstr + ft_strglen(s1), s2, ft_strglen(s2));
	nstr[ft_strglen(s1) + ft_strglen(s2)] = '\0';
	return (nstr);
}

static char			*ft_strgdup(char *s, size_t len)
{
	char *nstr;

	if (!(nstr = (char*)malloc(sizeof(nstr) * (len + 1))))
		return (NULL);
	ft_strncpy(nstr, s, len);
	nstr[len] = '\0';
	return (nstr);
}

static int			make_new_line(char **save, char **line, char *str)
{
	char			*tmp;

	if (str != NULL)
	{
		*line = ft_strgdup(*save, str - *save);
		tmp = ft_strgdup(str + 1, ft_strglen(str + 1));
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
		*line = ft_strgdup("", 1);
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
			tmp = ft_strgdup(buffer, len);
		else
			tmp = ft_strgjoin(save[fd], buffer);
		if (save[fd] != 0)
			free(save[fd]);
		save[fd] = tmp;
	}
	if (len < 0)
		return (-1);
	return (make_new_line(&save[fd], line, str));
}
