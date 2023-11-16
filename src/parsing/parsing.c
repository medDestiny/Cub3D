/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/16 11:57:26 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures_data(t_data **data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*data)->textures[i] = NULL;
		i++;
	}
}

// parses all map elements
// initializes the t_data structure
// ps init_map_elements is in readmap.c

void	parser(char **av, int ac, t_data *data)
{
	int	map_fd;

	map_fd = 0;
	if (ac != 2)
		ft_error(MAP_EXIST, data);
	init_textures_data(&data);
	map_fd = open_file(av[1], data);
	check_extension(av[1]);
	map_fd = init_map_elements(map_fd, &data, av[1]);
	close(map_fd);
}
