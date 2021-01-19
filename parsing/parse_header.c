/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 10:55:35 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/01/19 11:10:06 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_read_fd(int fd)
{
	char *str;

	str = read(fd, INT_MAX);
	return (str);
}

char	*ft_parse_resolution_len(char *str)
{
	char *res_len;
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'R')
		{	
			res_len = ft_atoi(str + (i + 1));
			break;
		}
		i++;
	}
	return (res_len);
}

char	*ft_parse_resolution_high(char *str)
{
	char *res_high;
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'R')
		{
			i += ft_strlen(ft_itoa(ft_atoi(str + (i + 1))));
			res_high = ft_atoi(str + (i + 1));
			break;
		}
		i++;
	}
	return (res_high);
}

char	*ft_north_path(char *str)
{
	char *n_path;
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == 'N' && str[i + 1] == 'O')
		{
			i += 3;
			while (str[i] != '\n')
			{
				n_path[j] = str[i];
				j++;
				i++;
			}
			break;
		}
		i++;
	}
}
