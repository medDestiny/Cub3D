/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 11:34:58 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/23 14:30:04 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
