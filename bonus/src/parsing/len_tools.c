/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:44:29 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 17:45:48 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	file_empty(int fd)
{
	char	*file_line;

	file_line = get_next_line(fd);
	if (!file_line)
	{
		close (fd);
		return (1);
	}
	free(file_line);
	close (fd);
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

//		 map_size inits to 1
//		 since we already read a line while checking elements 
size_t	get_map_size(int fd)
{
	size_t	map_size;
	char	*map_line;

	map_size = 1;
	while (1)
	{
		map_line = get_next_line(fd);
		if (!map_line || (map_line && map_line[0] == '\n'))
		{
			free(map_line);
			break ;
		}
		map_size++;
		free(map_line);
	}
	close(fd);
	return (map_size);
}
