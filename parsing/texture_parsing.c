/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:05:16 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/06 20:50:11 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_textures(mlx_texture_t **textures)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (textures[i] == NULL)
			return (-7);
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

void	find_textures(char **splitted, t_data **data, char *str_read)
{
	int	err;

	err = 0;
	if (ft_strcmp(splitted[0], "NO") == 0)
		err = load_texture(*data, splitted, NO, str_read);
	else if (ft_strcmp(splitted[0], "SO") == 0)
		err = load_texture(*data, splitted, SO, str_read);
	else if (ft_strcmp(splitted[0], "WE") == 0)
		err = load_texture(*data, splitted, WE, str_read);
	else if (ft_strcmp(splitted[0], "EA") == 0)
		err = load_texture(*data, splitted, EA, str_read);
	else
	{
		free_content(str_read, splitted, NULL);
		ft_error(INVA_CORD, *data);
	}
}

int	init_textures(int map_fd, t_data **data)
{
	char	*str_read;
	char	**splitted_str;
	
	while (1)
	{
		str_read = get_next_line(map_fd);
		if (!str_read || str_read[0] == '\n')
			break;
		splitted_str = ft_split(str_read, ' ');
		find_textures(splitted_str, data, str_read);
		free_content(str_read, splitted_str, NULL);
	}
	close(map_fd);
	if (check_textures((*data)->textures) == -7)
		ft_error(CORD_MIS, *data);
	return (0);
}


// Reads map and textures

void	read_textures(int map_fd, t_data **data, char *map_path)
{
	int		map_size;

	map_size = get_map_size(map_fd);
	if (map_size == 0)
		ft_error(MAP_EMPTY, *data);
	map_fd = open_file(map_path, *data);
	init_textures(map_fd, data);
}
