/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:12:40 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/27 21:48:58 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


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
