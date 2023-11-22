/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:12:40 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/22 18:04:48 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

// checks if one of the map lines is empty
// if true it throws an error frees and quits

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

// find elements function checks if input is a valid cord or color
// else it throws an error frees and quits
// ps : called loading functions are in load_elements.c

void	find_elements(char **splitted, t_data **data, char *str_read)
{
	if (ft_strcmp(splitted[0], "NO") == 0)
		load_texture(*data, splitted, NO, str_read);
	else if (ft_strcmp(splitted[0], "SO") == 0)
		load_texture(*data, splitted, SO, str_read);
	else if (ft_strcmp(splitted[0], "WE") == 0)
		load_texture(*data, splitted, WE, str_read);
	else if (ft_strcmp(splitted[0], "EA") == 0)
		load_texture(*data, splitted, EA, str_read);
	else if (ft_strcmp(splitted[0], "F") == 0)
		load_floor(*data, splitted);
	else if (ft_strcmp(splitted[0], "C") == 0)
		load_cieling(*data, splitted);
	else
	{
		free_content(str_read, splitted, NULL);
		ft_error(INVA_CORD, *data);
	}
}

// reads until map is detected since the map has its own seperate func
// then it calls the find elements func

int	read_elements(int map_fd, t_data **data)
{
	char	*str_read;
	char	**split_str;
	char	*tmp;

	while (1)
	{
		str_read = get_next_line(map_fd);
		if (str_read[0] == '\n')
			str_read = newline_iter(map_fd, str_read);
		if (!str_read || (str_read[0] && ft_isdigit(str_read[0]))
			|| str_read[0] == ' ')
		{
			free(str_read);
			break ;
		}
		tmp = str_read;
		str_read = ft_strtrim(str_read, "\n");
		free(tmp);
		split_str = ft_split(str_read, ' ');
		find_elements(split_str, data, str_read);
		free_content(str_read, split_str, NULL);
	}
	if (check_textures((*data)->textures) == CORD_MIS)
		ft_error(CORD_MIS, *data);
	return (map_fd);
}

// reads map elements coordinates / colors and map 
// and inits them using coressponding 

int	init_map_elements(int map_fd, t_data **data, char *map_path)
{
	int		map_size;
	char	**map;

	map = NULL;
	map_size = get_map_size(map_fd);
	if (map_size == 0)
		ft_error(MAP_EMPTY, *data);
	map_fd = open_file(map_path, *data);
	map_fd = read_elements(map_fd, data);
	map = get_parsed_map(map_fd, map_path, *data);
	check_map_spaces(map, *data);
	init_map(map, *data);
	free_arr(map);
	return (map_fd);
}
