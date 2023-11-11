/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:44:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/11 20:22:21 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	parse_map(char **map, t_data *data)
{
	int	i;
	int	map_size;

	i = 0;
	map_size = 0;
	while(map[map_size])
		map_size++;
	if (map_size < 3)
		ft_error(MAP_INV, data);
	data->player_flag = 0;
	while (map[i])
	{
		if (i == 0)
		{
			printf("in first %s\n", map[i]);
			parse_map_fl(map[i], data);
		}
		else if (i == (map_size - 1))
		{
			printf("in last %s\n", map[i]);
			parse_map_fl(map[i], data);
		}
		else if ( i > 0 && i < map_size )
		{
			printf("in second %s\n", map[i]);
			parse_map_m(map[i], data);
		}
		i++;
		printf("%d\n", i);
	}
}

void	check_map_spaces(char **map, t_data *data)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (map[i])
	{
		if (map[i][0] == ' ')
		{
			while (map[i][d] && map[i][d] == ' ')
				d++;
			if (map[i][d] == '\0')
				ft_error(MAP_INV, data);
		}
		d = 0;
		i++;
	}
}

char	*skip_map_elements(int map_fd)
{
	char *str_read;
	int	i;
	
	i = 0;
	while (1)
	{
		str_read = get_next_line(map_fd);
		while (str_read && str_read[i] == ' ')
			i++;
		if (!str_read || ft_isdigit(str_read[0]) == 1)
			return (str_read);
		i = 0;
		free(str_read);
	}
}

char	**get_map(int map_fd, char *map_path, t_data *data)
{
	size_t	map_size;
	char	*str_read;
	char	**map;
	size_t		i;

	map_size = get_map_size(map_fd);
	str_read = NULL;
	map = malloc(sizeof(char *) * (map_size + 1));
	i = 0;
	if (map_size == 0 || !map)
		ft_error(MAP_INV, data);
	map_fd = open_file(map_path, data);
	str_read = skip_map_elements(map_fd);
	map[map_size] = NULL;
	while (i < map_size)
	{
		map[i] = str_read;
		str_read = get_next_line(map_fd);
		if (!str_read)
			break;
		free(str_read);
		i++;
	}
	close(map_fd);
	return (map);
}


