/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:43:57 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/01 17:47:25 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

size_t	calc_unit(t_data *data)
{
	(void)data;
	return  ((data->game->width + data->game->height) / 250);
}

void	draw_map(t_data *data)
{
	mlx_image_t	*map_img;
	t_ivec	p;
	size_t	i;
	size_t	d;
	size_t	unit;

	i = 0;
	d = 0;
	unit = calc_unit(data);
	printf("%zu\n", unit);
	map_img = mlx_new_image(data->mlx, data->game->width, data->game->height);
	p.y = (data->game->height / 2) + (data->game->height / 4);
	p.x = data->game->width / 2;
	while (data->map[i])
	{
		while (data->map[i][d])
		{
			if (data->map[i][d] == '2')
				draw_square(map_img, p, unit, 0x06FF00AA);
			if (data->map[i][d] == '3')
				draw_square(map_img, p, unit, 0x06FF0011);
			if (data->map[i][d] == '1')
				draw_square(map_img, p, unit, 0x06FF00FF);
			if (data->map[i][d] == '0')
				draw_square(map_img, p, unit, 0x000000FF);
			d++;
			p.x += unit;
		}
		i++;
		p.y += unit;
		d = 0;
		p.x = data->game->width / 2;
	}
	draw_player(map_img, data->player, unit);
	mlx_image_to_window(data->mlx, map_img, 0, 0);
}

