/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:05:16 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/08 18:15:30 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char *newline_iter(int map_fd, char *str_read)
{
	while (1)
	{
		if(str_read && str_read[0] == '\n')
		{
			free(str_read);
			str_read = get_next_line(map_fd);
			printf("in iter %s\n", str_read);
		}
		else
			break;
	} 
	return (str_read);
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

// frees the line read by get_next_line and the splitted string used

void	free_content(char *str, char **splitted_str, char *trimmed)
{
	int	i;

	i = 0;
	free(str);
	free (trimmed);
	while (splitted_str[i])
	{
		free(splitted_str[i]);
		i++;
	}
}

int	load_texture(t_data *data, char **str, int index, char *str_read)
{
	char	*path;

	path = ft_strtrim(str[1], "\n");
	if (data->textures[index] != NULL)
	{
		free_content(path, str, str_read);
		ft_error(DUP_CORD, data);
	}
	data->textures[index] = mlx_load_png(path);
	if (data->textures[index] == NULL)
	{
		free_content(path, str, str_read);
		ft_error(TEX_LOAD_ERR, data);
	}
	free(path);
	return (0);
}

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

int	init_elements(int map_fd, t_data **data)
{
	char	*str_read;
	char	**split_str;
	
	while (1)
	{
		str_read = get_next_line(map_fd);
		if (str_read[0] == '\n')
			str_read = newline_iter(map_fd, str_read);
		if (!str_read || (str_read[0] && ft_isdigit(str_read[0])))
			break;
		split_str = ft_split(str_read, ' ');
		if (ft_arraylen(split_str) != 2)
		{
			free_content(str_read, split_str, NULL);
			ft_error(INV_INPUT, *data);
		}
		printf("|%s|\n", split_str[0]);
		find_elements(split_str, data, str_read);
		free_content(str_read, split_str, NULL);
	}
	free_content(str_read, split_str, NULL);
	if (check_textures((*data)->textures) == CORD_MIS)
		ft_error(CORD_MIS, *data);
	return (map_fd);
}


// Reads map and textures

int	read_map_elements(int map_fd, t_data **data, char *map_path)
{
	int		map_size;

	map_size = get_map_size(map_fd);
	if (map_size == 0)
		ft_error(MAP_EMPTY, *data);
	map_fd = open_file(map_path, *data);
	map_fd = init_elements(map_fd, data);
	// init_map();
	return(map_fd);
}
