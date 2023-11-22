/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:00:00 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/22 18:25:33 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_wall_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

size_t	arr_len(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
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

// map_size inits to 1 since we already read a line while checking elements 

size_t	get_map_size(int fd)
{
	size_t	map_size;
	char	*map_line;

	map_size = 1;
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line)
			break ;
		if (map_line && ft_strlen(map_line) > 0)
			map_size++;
		else if (map_line && !ft_strlen(map_line) && map_size != 0)
		{
			free(map_line);
			close(fd);
			return (0);
		}
		free(map_line);
	}
	close(fd);
	return (map_size);
}

int	open_file(char *str, t_data *data)
{
	int	map_fd;

	map_fd = open(str, O_RDONLY);
	if (map_fd == -1)
	{
		ft_error(OPEN_ERR, data);
		exit(OPEN_ERR);
	}
	return (map_fd);
}
