/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_cieling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 22:25:41 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/06 22:51:56 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	load_floor(t_data *data, char **split)
{
	
}
int	load_cieling(t_data *data, char **split)
{
	
}

void	find_cieling(char **split, t_data *data)
{
	int err;

	err = 0;
	if (ft_strcmp(split[0], "C") == 0)
		err = load_cieling(data, split);
	else
		ft_error(CIELING_INV, data);
}

void	find_floor(char **split, t_data *data)
{
	int err;

	err = 0;
	if (ft_strcmp(split[0], "F") == 0)
		err = load_floor(data, split);
	else
		ft_error(FLOOR_INV, data);
}

void	fl_cl_check(int map_fd, t_data *data)
{
	char *str_read;
	char **splitted_str;

	while (1)
	{
		str_read = get_next_line(map_fd);
		if (!str_read || str_read[0] == '\n')
			break;
		splitted_str = ft_split(str_read, ' ');
		find_fl_cl(splitted_str, data);
	}
	
	
}