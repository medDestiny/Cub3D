/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:44:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:42:56 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_map_fl(char *map_str, t_data *data)
{
	int	i;

	i = 0;
	if (!map_str)
		ft_error(MAP_INV, data, clean_parsing);
	while (map_str[i])
	{
		if (map_str[i] && (map_str[i] == '1' || map_str[i] == ' '))
			i++;
		else
			ft_error(MAP_INV, data, clean_parsing);
	}
}

static char	*skip_map_elements(int map_fd, t_data *data)
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
			ft_error(MAP_INV, data, clean_parsing);
		if (!str_read || ft_isdigit(str_read[i]) == 1)
			return (str_read);
		free(str_read);
	}
}

static void	fill_map(t_data *data, char *str_read, int map_fd, size_t map_size)
{
	size_t	i;

	i = 0;
	while (i < map_size)
	{
		check_entities(data, str_read, i);
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
	if (data->goal == NULL)
		ft_error(GOAL_MIS, data, clean_parsing);
	if (data->player == NULL)
		ft_error(PLAYER_MIS, data, clean_parsing);
	if (data->enemy == NULL)
		ft_error(ENEMY_MIS, data, clean_parsing);
}

void	get_parsed_map(int map_fd, char *map_path, t_data *data)
{
	size_t	map_size;
	char	*str_read;

	map_size = get_map_size(map_fd);
	data->map = ft_malloc(sizeof(char *) * (map_size + 1), data, clean_parsing);
	data->saved_map = ft_malloc(sizeof(char *)
			* (map_size + 1), data, clean_parsing);
	if (map_size == 1 || !data->map)
		ft_error(MAP_INV, data, clean_parsing);
	map_fd = open_file(map_path, data);
	str_read = skip_map_elements(map_fd, data);
	fill_map(data, str_read, map_fd, map_size);
	check_map_leftovers(map_fd, data);
	close(map_fd);
}
