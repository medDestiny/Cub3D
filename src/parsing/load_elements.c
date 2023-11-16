/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:19:12 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/12 20:31:01 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// parses and loads floor colors

void	load_floor(t_data *data, char **split)
{
	char	*color;
	char	**colors;

	color = ft_strtrim(split[1], "\n");
	if (comma_count(color) == -1)
		ft_error(FLOOR_INV, data);
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3)
		ft_error(FLOOR_INV, data);
	if (parse_color(colors) == FLOOR_INV)
		ft_error(FLOOR_INV, data);
	data->floor_color = merge_rgba(colors, data);
	data->floor_flag = 1;
}

// parses and loads cieling colors

void	load_cieling(t_data *data, char **split)
{
	char	*color;
	char	**colors;
	
	color = ft_strtrim(split[1], "\n");
	if (comma_count(color) == -1)
		ft_error(FLOOR_INV, data);
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3)
		ft_error(CIELING_INV, data);
	if (parse_color(colors) != 0)
		ft_error(CIELING_INV, data);
	data->cieling_color = merge_rgba(colors, data);
	data->cieling_flag = 1;
}

// parses and loads the texture to coressponding cordinate

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
