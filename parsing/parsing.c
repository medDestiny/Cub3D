/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:50:07 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/06 22:02:03 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	check_extension(char *str)
{
	char	*exten;
	int		i;
	int		d;

	exten = ".cub";
	i = ft_strlen(str);
	d = ft_strlen(exten);
	if (i < 5)
	{
		ft_error(EXT_ERR, NULL);
		exit(EXT_ERR);
	}
	while (i > 0 && d > 0)
	{
		if (exten[d] == str[i])
		{
			i--;
			d--;
		}
		else
		{
			ft_error(EXT_ERR, NULL);
			exit(EXT_ERR);
		}
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

// checks if map is entered / valid extension /valid textures /

void	parser(char **av, int ac, t_data *data)
{
	int	map_fd;

	map_fd = 0;
	init_textures_data(&data);
	if (ac != 2)
		ft_error(MAP_EXIST, data);
	map_fd = open_file(av[1], data);
	check_extension(av[1]);
	read_textures(map_fd, &data, av[1]);
	
}
