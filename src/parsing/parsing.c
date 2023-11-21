/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/21 13:56:29 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_extension(char *str)
{
	char	*exten;
	int		i;
	int		d;

	exten = ".cub";
	i = ft_strlen(str);
	d = ft_strlen(exten);
	if (i < 5)
		ft_error(EXT_ERR, NULL);
	while (i > 0 && d > 0)
	{
		if (exten[d] == str[i])
		{
			i--;
			d--;
		}
		else
			ft_error(EXT_ERR, NULL);
	}		
}

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
