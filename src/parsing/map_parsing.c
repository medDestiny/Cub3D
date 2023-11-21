/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:28:46 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/21 18:03:33 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	get_biggest_line(char **map)
{
	size_t	i;
	size_t	biggest_line;

	i = 0;
	biggest_line = 0;
	if (map[i])
		biggest_line = ft_strlen(map[i]);
	while (map[i])
	{
		if (ft_strlen(map[i]) > biggest_line)
			biggest_line = ft_strlen(map[i]);
		i++;
	}
	return (biggest_line);
}

static int	check_lines(char *line, char *prev_line)
{
	size_t	i;
	size_t	len;
	size_t	prv_len;

	i = 0;
	len = ft_strlen(line) - 1;
	prv_len = ft_strlen(prev_line) - 1;
	if (prev_line[prv_len] != '1')
		return (MAP_LEN);
	printf("line len  |%zu|\n", ft_strlen(line));
	while(line[prv_len] && prv_len < ft_strlen(line))
	{
		if (line[prv_len] != '1' && !prev_line[ft_strlen(line) - 2])
		{
			return (MAP_LEN);
		}
		else if (line[prv_len] != '1' && prev_line[ft_strlen(line) - 2] != '1')
		{
			return (MAP_LEN);
		}
		printf("line index |%zu|\n", prv_len);
		prv_len++;
	}
	puts("________out_______\n");
	return (0);
}

void	parse_map_len(char **map)
{
	size_t	i;
	size_t	prev_len;

	i = 1;
	prev_len = ft_strlen(map[0]);
	while (map[i])
	{	
		if ((map[i] && map[i - 1]) 
			&& (prev_len <= ft_strlen(map[i]))
				&& check_lines(map[i], map[i -1]) == MAP_LEN)
				{
					printf("%s\n", map[i]);
					ft_putstr_fd("MAP LEN ERR\n", 2);
					exit (1);
				}
		printf("%zu\n", prev_len);
		prev_len = ft_strlen(map[i]);
		i++;
	}
}

static size_t	array_len(char **arr)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (arr[i])
	{		
		if (arr[i][0] == '1')
			size++;
		i++;
	}
	return (size);
}

// checks if the map's line is empty
// aka only containing spaces

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


// parses the map in three seperate functions
// parse_map_fl for the first and last lines
// parse_map_m for the middle of the map
// aka anything besides the first and last lines

void	parse_map(char **map, t_data *data)
{
	int	y;
	int	map_size;

	y = 0;
	map_size = 0;
	while(map[map_size])
		map_size++;
	if (map_size < 3)
	{
		free_arr(map);
		ft_error(MAP_INV, data);
	}
	data->player_flag = 0;
	while (map[y])
	{
		if (check_empty(map[y]) == -1)
		{
			free_arr(map);
			ft_error(MAP_INV, data);
		}
		if (y == 0)
			parse_map_fl(map[y], data);
		else if (y == (map_size - 1))
			parse_map_fl(map[y], data);
		else if ( y > 0 && y < map_size )
			parse_map_m(map[y], data, y);
		y++;
	}
}

// calls parse_map to see if the map is valid
// fills the data structure's 2d array with corresponding map

void	init_map(char **map, t_data *data)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = array_len(map);
	data->map = (char **)malloc((size + 1) * sizeof(char *));
	data->map[size] = NULL;
	while (i < size && map[i])
	{
		data->map[i] = ft_strtrim(map[i], "\n");
		i++;
	}
	parse_map_len(data->map);
	parse_map(data->map, data);
}
