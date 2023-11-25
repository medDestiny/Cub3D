/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:44:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/24 18:01:43 by mmisskin         ###   ########.fr       */
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

	while (1)
	{
		i = 0;
		str_read = get_next_line(map_fd);
		while (str_read[i] && str_read[i] == ' ')
			i++;
		if (str_read && str_read[0] != '\n'
			&& (str_read[i] == '\0' || str_read[i] == '\n'))
			ft_error(MAP_INV, data);
		if (!str_read || ft_isdigit(str_read[i]) == 1)
			return (str_read);
		free(str_read);
	}
}

void	fill_map(t_data *data, char *str_read, int map_fd, size_t map_size)
{
	size_t	i;

	i = 0;
	while (i < map_size)
	{
		check_player(data, str_read, i);
		data->map[i] = ft_strtrim(str_read, "\n");
		free(str_read);
		str_read = get_next_line(map_fd);
		if (!str_read || (str_read && str_read[0] == '\n'))
		{
			free(str_read);
			break ;
		}
		i++;
	}
	data->map[map_size] = NULL;
}

void	get_parsed_map(int map_fd, char *map_path, t_data *data)
{
	size_t	map_size;
	char	*str_read;

	map_size = get_map_size(map_fd);
	data->map = ft_malloc(sizeof(char *) * (map_size + 1), data);
	if (map_size == 1 || !data->map)
		ft_error(MAP_INV, data);
	map_fd = open_file(map_path, data);
	str_read = skip_map_elements(map_fd, data);
	fill_map(data, str_read, map_fd, map_size);
	check_map_leftovers(map_fd, data);
	close(map_fd);
}
