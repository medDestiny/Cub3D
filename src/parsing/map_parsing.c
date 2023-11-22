/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/22 18:39:15 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_lines(char **map, size_t i, size_t pos)
{
	if (pos == 0 || pos == (ft_strlen(map[i]) - 1)
		|| i == 0 || i == arr_len(map) - 1)
		return (MAP_INV);
	if (map[i][pos - 1] != '1' && check_wall_player(map[i][pos - 1]) == 0) // left
		return (MAP_INV);
	if (map[i][pos + 1] != '1' && check_wall_player(map[i][pos + 1]) == 0) // right
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) < pos) // checks if the len of the previous line is less than index
		return (MAP_INV);
	if (ft_strlen(map[i - 1]) >= pos) // checks if the previous line has a valid character or not 
	{
		if (map[i - 1][pos] != '1' && check_wall_player(map[i - 1][pos]) == 0)
			return (MAP_INV);
	}
	if (ft_strlen(map[i + 1]) < pos) // checks if the len of the forward line is less than index
		return (MAP_INV);
	else if (ft_strlen(map[i + 1]) >=  pos) // checks if the forward line has a valid character or not 
	{
		if (map[i + 1][pos] != '1' && check_wall_player(map[i + 1][pos]) == 0)
			return (MAP_INV);
	}
	return (0);
}

void	parse_map_len(char **map, t_data *data)
{
	size_t	i;
	size_t	pos;

	i = 1; 
	pos = 0;
	parse_map_fl(map[0], data);
	parse_map_fl(map[arr_len(map) -1], data);
	while (map[i] && i < (arr_len(map) - 1))
	{
		while (map[i][pos])
		{
			if (check_wall_player(map[i][pos]) == 1)
			{
				if (check_lines(map, i, pos) == MAP_INV)
					ft_error(MAP_INV, data);
			}
			else if (map[i][pos] != '1' && map[i][pos] != ' ')
				ft_error(MAP_INV, data);
			pos++;
		}
		pos = 0;
		i++;
	}
}

/*
* checks if the map's line is empty
* aka only containing spaces
*/

int	check_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (0);
}

/*
* parses the map in three seperate functions
* parse_map_fl for the first and last lines
* parse_map_m for the middle of the map
* aka anything besides the first and last lines
*/

void	parse_map(char **map, t_data *data)
{
	int	y;
	int	map_size;

	y = 0;
	map_size = arr_len(map);
	if (map_size < 3)
	{
		free_arr(map);
		ft_error(MAP_INV, data);
	}
	data->player_flag = 0;
	while (map[y])
	{
		if (y == 0)
			parse_map_fl(map[y], data);
		else if (y == (map_size - 1))
			parse_map_fl(map[y], data);
		y++;
	}
}
/*
* calls parse_map to see if the map is valid
* fills the data structure's 2d array with corresponding map
*/

void	init_map(char **map, t_data *data)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = arr_len(map);
	if (size < 3)
	{
		free_arr(map);
		ft_error(MAP_INV, data);
	}
	data->map = (char **)malloc((size + 1) * sizeof(char *));
	while (i < size && map[i])
	{
		data->map[i] = ft_strtrim(map[i], "\n");
		i++;
	}
	data->map[size] = NULL;
	parse_map_len(data->map, data);
}
