/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 11:13:11 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/05/20 13:57:07 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	check_first_line(char *line, t_recup *recup)
{
	if (ft_strchr(line, '0') != NULL)
		recup->erreur = 1;
}

void	check_item(char c, t_recup *recup)
{
	if (c == '0')
		recup->erreur = 1;
}

int		check_letter(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (2);
	else if (c != ' ' && c != '1' && c != '2' && c != 'N' && c != 'E' &&
			c != 'W' && c != 'S')
		return (1);
	return (0);
}

void	check_line(char *str, t_recup *recup, int i)
{
	int j;

	j = -1;
	while (str[++j])
	{
		if (j == 0)
			check_item(str[j], params);
		else if (j == (int)(ft_strlen(str) - 1))
		{
			check_item(str[j], params);
			break ;
		}
		else if (str[j] == '0')
		{
			if (recup->map[i - 1][j] == ' ' || recup->map[i + 1][j] == ' ' ||
					str[j - 1] == ' ' || str[j + 1] == ' ')
				recup->erreur = 1;
			if (ft_strlen(recup->map[i - 1]) <= (size_t)j ||
					ft_strlen(recup->map[i + 1]) <= (size_t)j)
				recup->erreur = 1;
		}
		else if (check_letter(str[j]) == 1)
			recup->erreur = 1;
	}
}

int		check_map(t_recup *recup)
{
	int i;

	i = 0;
	while (recup->map[i])
	{
		if (i == 0)
		{
			check_first_line(recup->map[i], params);
			i++;
			continue;
		}
		else if (i == (int)(ft_strlen(*recup->map) - 1))
		{
			check_first_line(recup->map[i], params);
			break ;
		}
		else
			check_line(map[i], recup, i);
		i++;
	}
	return (0);
}
