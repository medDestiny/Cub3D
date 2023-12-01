/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:34:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/01 17:45:59 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
 * checks if one of the map lines is empty
 * if true it throws an error frees and quits
 */

void	check_map_spaces(t_data *data)
{
	size_t	i;
	size_t	d;

	i = 0;
	while (data->map[i])
	{
		d = 0;
		if (data->map[i] && data->map[i][0] == ' ')
		{
			while (data->map[i][d] && data->map[i][d] == ' ')
				d++;
			if (data->map[i][d] == '\0' || data->map[i][d] == '\n')
				ft_error(MAP_INV, data, clean_parsing);
		}
		i++;
	}
}


int	check_textures(mlx_texture_t **textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i] == NULL)
			return (CORD_MIS);
		i++;
	}
	return (0);
}

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
		ft_error(DOOR_ERR, data, clean_parsing);
}

int	check_lines(char **map, size_t i, size_t pos, t_data *data)
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

void	check_map_leftovers(int fd, t_data *data)
{
	char	*str_read;

	str_read = NULL;
	while (1)
	{
		str_read = get_next_line(fd);
		if (!str_read)
			break ;
		if (str_read[0] != '\n')
		{
			free(str_read);
			ft_error(MAP_INV, data, clean_parsing);
		}
		free(str_read);
	}
}
