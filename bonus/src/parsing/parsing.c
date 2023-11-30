/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/30 13:27:27 by mmisskin         ###   ########.fr       */
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
		ft_error(EXT_ERR, NULL, clean_parsing);
	while (i > 0 && d > 0)
	{
		if (exten[d] == str[i])
		{
			i--;
			d--;
		}
		else
			ft_error(EXT_ERR, NULL, clean_parsing);
	}
}

static void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->goal = NULL;
	data->mlx = NULL;
	data->image = NULL;
	data->map = NULL;
	data->enemy = NULL;
	data->player = NULL;
	data->astar = NULL;
	data->sprites = NULL;
	data->zbuffer = NULL;
	while (i < 4)
	{
		data->textures[i] = NULL;
		i++;
	}
	data->door = mlx_load_png("assets/textures/door_close.png");
	if (!data->door)
		ft_error(DOOR_ERR, data, clean_parsing);
}

/*
 * parses all map elements
 * initializes the t_data structure
 * ps init_map_elements is in readmap.c
 */

void	parser(char **av, int ac, t_data *data)
{
	int	map_fd;

	init_data(data);
	if (ac != 2)
		ft_error(ARG_ERR, data, clean_parsing);
	check_extension(av[1]);
	map_fd = open_file(av[1], data);
	init_map_elements(map_fd, data, av[1]);
	close(map_fd);
}
