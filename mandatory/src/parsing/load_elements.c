/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:19:12 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/26 11:31:15 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	comma_count(char *colors)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (colors[i])
	{
		if (colors[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count != 2)
		return (-1);
	return (0);
}

// parses and loads floor colors
void	load_floor(t_data *data, char **split)
{
	static short int	flag;
	char				*color;
	char				**colors;

	color = ft_strtrim(split[1], "\n");
	if (flag == 1)
	{
		free_content(color, split, NULL);
		ft_error(DUP_COLOR, data);
	}
	if (comma_count(color) == -1)
	{
		free_content(color, split, NULL);
		ft_error(FLOOR_INV, data);
	}
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3 || parse_color(colors) != 0)
	{
		free_content(color, split, NULL);
		ft_error(FLOOR_INV, data);
	}
	data->floor_color = merge_rgba(colors, data);
	flag = 1;
	free_content(color, colors, NULL);
}

// parses and loads cieling colors
void	load_cieling(t_data *data, char **split)
{
	static short int	flag;
	char				*color;
	char				**colors;

	color = ft_strtrim(split[1], "\n");
	if (flag == 1)
	{
		free_content(color, split, NULL);
		ft_error(DUP_COLOR, data);
	}
	if (comma_count(color) == -1)
	{
		free_content(color, split, NULL);
		ft_error(CIELING_INV, data);
	}
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3 || parse_color(colors) != 0)
	{
		free_content(color, colors, NULL);
		clean_vec(split);
		ft_error(CIELING_INV, data);
	}
	data->ceiling_color = merge_rgba(colors, data);
	flag = 1;
	free_content(color, colors, NULL);
}

char	*get_path(char *str_read, t_data *data)
{
	int		i;
	int		d;
	char	*path;

	i = 0;
	d = 0;
	path = NULL;
	while (str_read[i] && str_read[i] != ' ')
		i++;
	while (str_read[i] && str_read[i] == ' ')
		i++;
	if (i > 0)
		path = ft_malloc(((ft_strlen(str_read) - i) + 1) * sizeof(char), data);
	while (str_read[i])
		path[d++] = str_read[i++];
	path[d] = 0;
	return (path);
}

// parses and loads the texture to coressponding cordinate
int	load_texture(t_data *data, char **str, int index, char *str_read)
{
	char	*path;

	path = get_path(str_read, data);
	if (arr_len(str) < 2)
	{
		free_content(path, str, str_read);
		ft_error(CORD_MIS, data);
	}
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
