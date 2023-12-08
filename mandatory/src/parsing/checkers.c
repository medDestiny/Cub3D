/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:34:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/08 01:46:57 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_colors(t_data *data)
{
	if (data->floor_color == -1)
		ft_error(FLOOR_MIS, data);
	if (data->ceiling_color == -1)
		ft_error(CEIL_MIS, data);
}

void	check_map_leftovers(int fd, t_data *data)
{
	char	*str_read;

	str_read = NULL;
	while (1)
	{
		str_read = get_next_line(fd);
		if (!str_read)
			break ;
		if (str_read[0] != '\n')
		{
			free(str_read);
			ft_error(MAP_INV, data);
		}
		free(str_read);
	}
}
