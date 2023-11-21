/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:44:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/21 13:56:12 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*space_iter(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] == ' ')
		i++;
	return (str);
}

void	parse_map_fl(char *map_str, t_data *data)
{
	int	i;
	
	i = 0;
	map_str = ft_strtrim(map_str, "\n");
	if (!map_str)
		ft_error(MAP_INV, data);
	map_str = space_iter(map_str);
	if (!map_str)
		ft_error(MAP_INV, data);
	while (map_str[i])
	{
		if (map_str[i] && (map_str[i] == '1' || map_str[i] == ' '))
			i++;
		else
			ft_error(MAP_INV, data);
	}
	free(map_str);
}

void	parse_map_m(char *map_str, t_data *data, int y)
{
	int	x;
	
	x = 0;
	map_str = ft_strtrim(map_str, "\n");
	if (!map_str)
		ft_error(MAP_INV, data);
	map_str = space_iter(map_str);
	if (!map_str)
		ft_error(MAP_INV, data);
	if (map_str[0] != '1' && map_str[x] != ' ')
		ft_error(MAP_INV, data);
	while (map_str[x])
	{
		if (check_player(map_str[x], data, x, y) == -1)
			ft_error(MAP_INV, data);
		if (map_str[x] == '1' || map_str[x] == ' ' || map_str[x] == '0'
			|| map_str[x] == 'N' || map_str[x] == 'S'|| map_str[x] == 'E' || map_str[x] == 'W')
			x++;
		else
			ft_error(MAP_INV, data);
	}
	free(map_str);
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

char	**get_parsed_map(int map_fd, char *map_path, t_data *data)
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
		i++;
	}
	close(map_fd);
	return (map);
}
