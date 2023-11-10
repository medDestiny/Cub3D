/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cieling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:25:41 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/09 13:23:41 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

uint32_t	merge_rgba(char **colors, t_data *data)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;
	int			i;
	
	r = ft_atoi(colors[0]);
	g = ft_atoi(colors[1]);
	b = ft_atoi(colors[2]);
	a = 255;
	i = 0;
	if (r > 255 | g > 255 | b > 255)
		ft_error(COLOR_RANGE, data);
	return (r | g | b | a);
}

int	ft_arraylen(char **arr)
{
	int	i;
	
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int	parse_color(char **colors)
{
	int	i;
	int	d;

	i = 0;
	d = 0;
	while (colors[i])
	{
		while (colors[i][d])
		{
			if (ft_isdigit(colors[i][d]) == 1)
				d++;
			else
				return(FLOOR_INV);
		}
		i++;
		d = 0;
	}
	return (0);
}

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
