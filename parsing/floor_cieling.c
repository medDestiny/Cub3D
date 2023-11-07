/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cieling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:25:41 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/07 22:02:13 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		if (colors[i][d] && ft_isdigit(colors[i][d]) == 1)
		{
			while (colors[i][d] && ft_isdigit(colors[i][d]) == 1)
				d++;
			if (colors[i][d] != '\0') 
				return (-12);
		}
		else
			return(-12);
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
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3)
		ft_error(FLOOR_INV, data);
	if (parse_color(colors) != 0)
		ft_error(FLOOR_INV, data);
	data->floor_flag = 1;
	// data->floor_color;
}
void	load_cieling(t_data *data, char **split)
{
	char	*color;
	char	**colors;
	
	color = ft_strtrim(split[1], "\n");
	colors = ft_split(color, ',');
	if (ft_arraylen(colors) != 3)
		ft_error(FLOOR_INV, data);
	if (parse_color(colors) != 0)
		ft_error(CIELING_INV, data);
	data->cieling_flag = 1;
	// data->cieling_color;
}

void	find_flr_cln(char **f_arr, char **c_arr, t_data *data)
{
	int	f_flag;
	int	c_flag;
	
	f_flag = 0;
	c_flag = 0;	
	if (ft_strcmp(f_arr[0], "F") == 0 && f_arr[1]
		&& c_flag != 1)
		{
			puts("entered f");
			load_floor(data, f_arr);
			f_flag = 1;
		}
	else
		ft_error(FLOOR_INV, data);
	if (ft_strcmp(c_arr[0], "C") == 0 && c_arr[1]
		&& f_flag == 1)
		{
			puts("entered c");
			load_floor(data, c_arr);
			c_flag = 1;	
		}
	else
		ft_error(CIELING_INV, data);
}

void	fl_cl_check(int map_fd, t_data *data)
{
	char *str_read;
	char **floor_arr;
	char **cieling_arr;

	while (1)
	{
		str_read = get_next_line(map_fd);
		if (ft_strcmp(str_read, "\n") != 0)
			break;
	}
	floor_arr = ft_split(str_read, ' ');
	free(str_read);
	str_read = get_next_line(map_fd);
	cieling_arr = ft_split(str_read, ' ');
	free(str_read);
	str_read = get_next_line(map_fd);
	if (str_read[0] != '\n')
			ft_error(DUP_COLOR, data);
	if (ft_arraylen(floor_arr) != 2 && ft_arraylen(cieling_arr) != 2)
			ft_error(INV_INPUT, data);
	else
		find_flr_cln(floor_arr, cieling_arr, data);
}
