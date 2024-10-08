/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/05 12:05:38 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	parse_map_len(t_data *data)
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
			if (check_floor_player(data->map[i][pos]) == 1)
			{
				if (check_lines(data->map, i, pos, data) == MAP_INV)
					ft_error(MAP_INV, data, clean_parsing);
			}
			else if (data->map[i][pos] != '1' && data->map[i][pos] != ' ')
			{
				ft_error(MAP_INV, data, clean_parsing);
			}
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
		ft_error(MAP_INV, data, clean_parsing);
	parse_map_len(data);
}
