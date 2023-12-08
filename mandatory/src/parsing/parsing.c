/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/08 01:42:59 by mmisskin         ###   ########.fr       */
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

static void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->ceiling_color = -1;
	data->floor_color = -1;
	data->map = NULL;
	data->player = NULL;
	while (i < 4)
	{
		data->textures[i] = NULL;
		i++;
	}
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
		ft_error(ARG_ERR, data);
	check_extension(av[1]);
	map_fd = open_file(av[1], data);
	init_map_elements(map_fd, data, av[1]);
	close(map_fd);
}
