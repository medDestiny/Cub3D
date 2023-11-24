/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:44:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/24 14:29:16 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_dup_player(t_data *data)
{
	size_t	i;
	size_t	pos;
	int		player_flag;

	i = 0;
	pos = 0;
	player_flag = 0;
	while (data->map[i])
	{
		while (data->map[i][pos])
		{
			if (data->map[i][pos] == 'N' || data->map[i][pos] == 'S'
				|| data->map[i][pos] == 'W' || data->map[i][pos] == 'E')
				player_flag++;
			pos++;
		}
		if (player_flag > 1)
			ft_error(PLAYER_DUP, data);
		pos = 0;
		i++;
	}
	if (player_flag == 0)
		ft_error(PLAYER_DUP, data);
}

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
	if (!map_str)
		ft_error(MAP_INV, data);
	while (map_str[i])
	{
		if (map_str[i] && (map_str[i] == '1' || map_str[i] == ' '))
			i++;
		else
			ft_error(MAP_INV, data);
	}
}

char	*skip_map_elements(int map_fd, t_data *data)
{
	char	*str_read;
	int		i;

	i = 0;
	while (1)
	{
		str_read = get_next_line(map_fd);
		while (str_read[i] && str_read[i] == ' ')
			i++;
		if (str_read && str_read[0] != '\n'
			&& (str_read[i] == '\0' || str_read[i] == '\n'))
			ft_error(MAP_INV, data);
		if (!str_read || ft_isdigit(str_read[i]) == 1)
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
	size_t	i;

	map_size = get_map_size(map_fd);
	str_read = NULL;
	map = malloc(sizeof(char *) * (map_size + 1));
	i = 0;
	if (map_size == 0 || !map)
		ft_error(MAP_INV, data);
	map_fd = open_file(map_path, data);
	str_read = skip_map_elements(map_fd, data);
	while (i < map_size)
	{
		map[i] = str_read;
		str_read = get_next_line(map_fd);
		if (!str_read || (str_read && str_read[0] == '\n'))
			break ;
		i++;
	}
	map[map_size] = NULL;
	check_map_leftovers(map_fd, data);
	close(map_fd);
	return (map);
}
