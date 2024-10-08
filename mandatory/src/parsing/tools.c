/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:00:00 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/24 16:23:42 by mmisskin         ###   ########.fr       */
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
		ft_error(OPEN_ERR, data);
	return (map_fd);
}
