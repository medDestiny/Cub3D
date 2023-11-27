/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/27 15:41:58 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_door(t_data *data, size_t i, size_t pos)
{
	int	flag;

	flag = 0;
	if (data->map[i][pos] != '2')
		return ;
	if (data->map[i][pos + 1] != '1'
			|| data->map[i][pos - 1] != '1')
		flag++;
	if (data->map[i - 1][pos] != '1'
			|| data->map[i + 1][pos] != '1')
		flag++;
	if (flag == 2)
		ft_error(DOOR_ERR, data);
}

static int	check_lines(char **map, size_t i, size_t pos, t_data *data)
{
	if (pos == 0 || pos == (ft_strlen(map[i]) - 1)
		|| i == 0 || i == arr_len(map) - 1)
		return (MAP_INV);
	if (map[i][pos - 1] != '1' && check_floor_player(map[i][pos - 1]) == 0)
		return (MAP_INV);
	if (map[i][pos + 1] != '1' && check_floor_player(map[i][pos + 1]) == 0)
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) < pos)
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) >= pos)
	{
		if (map[i - 1][pos] != '1' && check_floor_player(map[i - 1][pos]) == 0)
			return (MAP_INV);
	}
	if (ft_strlen(map[i + 1]) < pos)
		return (MAP_INV);
	else if (ft_strlen(map[i + 1]) >= pos)
	{
		if (map[i + 1][pos] != '1' && check_floor_player(map[i + 1][pos]) == 0)
			return (MAP_INV);
	}
	check_door(data, i, pos);
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
			if (check_floor_player(data->map[i][pos]) == 1)
			{
				if (check_lines(data->map, i, pos, data) == MAP_INV)
					ft_error(MAP_INV, data);
			}
			else if (data->map[i][pos] != '1' && data->map[i][pos] != ' ')
			{
				ft_error(MAP_INV, data);
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
	size_t	i;
	size_t	size;

	i = 0;
	size = arr_len(data->map);
	if (size < 3)
		ft_error(MAP_INV, data);
	parse_map_len(data);
}
