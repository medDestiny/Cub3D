/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:44:29 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/23 17:26:49 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	file_len(int fd)
{
	char	*file_line;
	size_t	map_len;
	
	file_line = NULL;
	map_len = 0;
	while (1)
	{
		file_line = get_next_line(fd);
		if (!file_line)
		{
			free(file_line);
			break ;
		}
		map_len++;
		free(file_line);
	}
	close (fd);
	return (map_len);
}