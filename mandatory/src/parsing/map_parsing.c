/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/05 12:16:01 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_lines(char **map, size_t i, size_t pos)
{
	if (pos == 0 || pos == (ft_strlen(map[i]) - 1)
		|| i == 0 || i == arr_len(map) - 1)
		return (MAP_INV);
	if (map[i][pos - 1] != '1' && check_wall_player(map[i][pos - 1]) == 0)
		return (MAP_INV);
	if (map[i][pos + 1] != '1' && check_wall_player(map[i][pos + 1]) == 0)
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) < pos)
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) >= pos)
	{
		if (map[i - 1][pos] != '1' && check_wall_player(map[i - 1][pos]) == 0)
			return (MAP_INV);
	}
	if (ft_strlen(map[i + 1]) < pos)
		return (MAP_INV);
	else if (ft_strlen(map[i + 1]) >= pos)
	{
		if (map[i + 1][pos] != '1' && check_wall_player(map[i + 1][pos]) == 0)
			return (MAP_INV);
	}
	return (0);
}

void	parse_map_len(t_data *data)
{
	size_t	i;
	size_t	pos;

	i = 1;
	pos = 0;
	parse_map_fl(data->map[0], data);
	parse_map_fl(data->map[arr_len(data->map) - 1], data);
	while (data->map[i] && i < (arr_len(data->map) - 1))
	{
		while (data->map[i][pos])
		{
			if (check_wall_player(data->map[i][pos]) == 1)
			{
				if (check_lines(data->map, i, pos) == MAP_INV)
					ft_error(MAP_INV, data);
			}
			else if (data->map[i][pos] != '1' && data->map[i][pos] != ' ')
				ft_error(MAP_INV, data);
			pos++;
		}
		pos = 0;
		i++;
	}
}

/*
* calls parse_map to see if the map is valid
* fills the data structure's 2d array with corresponding map
*/

void	parse_map(t_data *data)
{
	size_t	size;

	size = arr_len(data->map);
	if (size < 3)
		ft_error(MAP_INV, data);
	parse_map_len(data);
}
