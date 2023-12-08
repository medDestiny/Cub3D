/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:00:00 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/08 01:36:56 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_colors(t_data *data)
{
	if (data->floor_color == -1)
		ft_error(FLOOR_MIS, data, clean_parsing);
	if (data->ceiling_color == -1)
		ft_error(CEIL_MIS, data, clean_parsing);
}

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

int	check_floor_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == '2'
		|| c == 'e' || c == 'a' || c == 'G')
		return (1);
	return (0);
}

char	*newline_iter(int map_fd, char *str_read)
{
	while (1)
	{
		if (str_read && str_read[0] == '\n')
		{
			free(str_read);
			str_read = get_next_line(map_fd);
		}
		else
			break ;
	}
	return (str_read);
}

int	open_file(char *str, t_data *data)
{
	int	map_fd;

	map_fd = open(str, O_RDONLY);
	if (map_fd == -1)
		ft_error(OPEN_ERR, data, clean_parsing);
	return (map_fd);
}
