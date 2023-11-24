/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:12:40 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/24 17:50:53 by mmisskin         ###   ########.fr       */
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
				ft_error(MAP_INV, data);
		}
		i++;
	}
}

/*
 * find elements function checks if input is a valid cord or color
 * else it throws an error frees and quits
 * ps : called loading functions are in load_elements.c
 */

void	find_elements(char **splitted, t_data *data, char *str_read)
{
	if (ft_strcmp(splitted[0], "NO") == 0)
		load_texture(data, splitted, NO, str_read);
	else if (ft_strcmp(splitted[0], "SO") == 0)
		load_texture(data, splitted, SO, str_read);
	else if (ft_strcmp(splitted[0], "WE") == 0)
		load_texture(data, splitted, WE, str_read);
	else if (ft_strcmp(splitted[0], "EA") == 0)
		load_texture(data, splitted, EA, str_read);
	else if (ft_strcmp(splitted[0], "F") == 0)
		load_floor(data, splitted);
	else if (ft_strcmp(splitted[0], "C") == 0)
		load_cieling(data, splitted);
	else
	{
		free_content(str_read, splitted, NULL);
		ft_error(INVA_CORD, data);
	}
}

/*
 * reads until map is detected since the map has its own seperate func
 * then it calls the find elements func
 */

void	read_elements(int map_fd, t_data *data)
{
	char	*str_read;
	char	**split_str;
	char	*tmp;

	while (1)
	{
		str_read = get_next_line(map_fd);
		if (str_read && str_read[0] == '\n')
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
	if (check_textures(data->textures) == CORD_MIS)
		ft_error(CORD_MIS, data);
}

/*
 * reads map elements coordinates / colors and map 
 * and inits them using coressponding 
 */

void	init_map_elements(int map_fd, t_data *data, char *map_path)
{
	if (file_empty(map_fd))
		ft_error(MAP_EMPTY, data);
	map_fd = open_file(map_path, data);
	read_elements(map_fd, data);
	get_parsed_map(map_fd, map_path, data);
	check_map_spaces(data);
	parse_map(data);
	close(map_fd);
}
