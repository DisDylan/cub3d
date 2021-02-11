/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoinsu <dpoinsu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:57:26 by dpoinsu           #+#    #+#             */
/*   Updated: 2021/02/11 11:54:55 by dpoinsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void		check_first_line(char *line, t_params *params)
{
	if (ft_strchr(line, '0') != NULL)
		params->map_error = ft_strdup("Erreur map");
}

void		check_item(char c, t_params *params)
{
	if (c == '0')
		params->map_error = ft_strdup("Erreur map");
}

int		check_letter(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (2);
	else if (c != ' ' && c != '1' && c != '2' && c != 'N' && c != 'E' &&
			c != 'W' && c != 'S')
		return (1);
	return(0);
}

void		check_line(char **tab, int i, t_params *params)
{
	int j;

	j = 0;
	while (tab[i][j])
	{
		if (j == 0)
			check_item(tab[i][j], params);
		else if (j == (int)(ft_strlen(tab[i]) - 1))
		{
			check_item(tab[i][j], params);
			break;
		}
		else if (tab[i][j] == '0')
		{
			if (tab[i - 1][j] == ' ' || tab[i + 1][j] == ' ' ||
					tab[i][j - 1] == ' ' ||
					tab[i][j + 1] == ' ')
				params->map_error = ft_strdup("Erreur map");
			if (ft_strlen(tab[i - 1]) <= (size_t)j || ft_strlen(tab[i + 1]) <= (size_t)j)
				params->map_error = ft_strdup("Erreur map");
		}
		else if (check_letter(tab[i][j]) == 1)
				params->map_error = ft_strdup("Erreur map");
		else if (check_letter(tab[i][j]) == 2)
		{
			params->player_x = j;
			params->player_y = i;
		}
		j++;
	}
}

int		check_map(t_params *params)
{
	int i;

	i = 0;
	while (params->map[i])
	{
		if (i == 0)
		{
			check_first_line(params->map[i], params);
			i++;
			continue;
		}
		else if (i == (int)(ft_strlen(*params->map) - 1))
		{
			check_first_line(params->map[i], params);
			break;
		}
		else
			check_line(params->map, i, params);
		i++;
	}
	printf("les checks ok\n");
	if (params->map_error != NULL)
		return (0);
	return (1);
}
