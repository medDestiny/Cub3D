/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:19:12 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:44:58 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
		ft_error(DUP_COLOR, data, clean_parsing);
	}
	if (comma_count(color) == -1)
	{
		free_content(color, split, NULL);
		ft_error(FLOOR_INV, data, clean_parsing);
	}
	colors = ft_split(color, ',');
	if (arr_len(colors) != 3 || parse_color(colors) != 0)
	{
		free_content(color, split, NULL);
		ft_error(FLOOR_INV, data, clean_parsing);
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
		ft_error(DUP_COLOR, data, clean_parsing);
	}
	if (comma_count(color) == -1)
	{
		free_content(color, split, NULL);
		ft_error(CIELING_INV, data, clean_parsing);
	}
	colors = ft_split(color, ',');
	if (arr_len(colors) != 3 || parse_color(colors) != 0)
	{
		free_content(color, colors, NULL);
		clean_vec(split);
		ft_error(CIELING_INV, data, clean_parsing);
	}
	data->ceiling_color = merge_rgba(colors, data);
	flag = 1;
	free_content(color, colors, NULL);
}

static char	*get_path(char *str_read, t_data *data)
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
		path = ft_malloc(((ft_strlen(str_read) - i) + 1)
				* sizeof(char), data, clean_parsing);
	while (str_read[i])
		path[d++] = str_read[i++];
	path[d] = 0;
	return (path);
}

// 	parses and loads the texture to coressponding cordinate
int	load_texture(t_data *data, char **str, int index, char *str_read)
{
	char	*path;

	path = get_path(str_read, data);
	if (arr_len(str) < 2)
	{
		free_content(path, str, str_read);
		ft_error(CORD_MIS, data, clean_parsing);
	}
	if (data->textures[index] != NULL)
	{
		free_content(path, str, str_read);
		ft_error(DUP_CORD, data, clean_parsing);
	}
	data->textures[index] = mlx_load_png(path);
	if (data->textures[index] == NULL)
	{
		free_content(path, str, str_read);
		ft_error(TEX_LOAD_ERR, data, clean_parsing);
	}
	free(path);
	return (0);
}
