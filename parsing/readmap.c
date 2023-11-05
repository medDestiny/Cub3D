/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:12:40 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/06 00:01:46 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// frees the line read by get_next_line and the splitted string used

void	free_content(char *str, char **splitted_str)
{
	int	i;

	i = 0;
	free(str);
	while (splitted_str[i])
	{
		free(splitted_str[i]);
		i++;
	}
}

//helper function to fill more coordinates

int	fill_textures_helper(char **splitted_str, t_data **data)
{
	if (ft_strcmp(splitted_str[0], "WE") == 0)
	{
		if ((*data)->textures[2] == NULL)
			(*data)->textures[2] = mlx_load_png(splitted_str[1]);
		else
			return (-1);
	}
	if (ft_strcmp(splitted_str[0], "EA") == 0)
	{
		if ((*data)->textures[3] == NULL)
			(*data)->textures[3] = mlx_load_png(splitted_str[1]);
		else
			return (-1);
	}
	return (0);
}

//fills data struct with the corresponding textures and checks if a coordinate is duplicated 

int	fill_textures(int map_fd, t_data **data)
{
	char	*str_read;
	char	**splitted_str;

	while (1)
	{
		str_read = get_next_line(map_fd);
		if (!str_read)
			break ;
		splitted_str = ft_split(str_read, ' ');
		if (ft_strcmp(splitted_str[0], "NO") == 0)
		{
			if ((*data)->textures[0] == NULL)
				(*data)->textures[0] = mlx_load_png(splitted_str[1]);
			else
				return (-1);
		}
		if (ft_strcmp(splitted_str[0], "SO") == 0)
		{
			if ((*data)->textures[1] == NULL)
				(*data)->textures[1] = mlx_load_png(splitted_str[1]);
			else
				return (-1);
		}
		fill_textures_helper(splitted_str, data);
		free_content(str_read, splitted_str);
	}
	return (0);
}

// checks if one of the textures is NULL

int	check_textures(t_data **data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if ((*data)->textures[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

// Reads map and textures

int	readmap(int map_fd, t_data **data)
{
	// int		map_size;

	// map_size = get_map_size(map_fd);
	// if (map_size == 0)
	// {
	// 	ft_putstr_fd("Error : map file is empty !", 2);
	// 	return (-1);
	// }
	// if (fill_textures(map_fd, data) == -1 || check_textures(data) == -1)
	(void)map_fd;
	if (check_textures(data) == -1)
	{		
		ft_putstr_fd("Error : texture Error check if textures exist !", 2);
		return (-1);
	}
	// (*data)->map = (char **)malloc((map_size + 1) * sizeof(char *));
	// if (!(*data)->map)
	// 	return (-1);
	// fill_map(map_fd, (*data)->map);
	
	return (0);
}
