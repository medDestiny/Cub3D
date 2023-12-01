/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:43:57 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/01 18:50:30 by mmisskin         ###   ########.fr       */
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
	//mlx_image_t	*map_img;
	t_ivec	p;
	t_ivec	s;
	t_ivec	e;
	t_ivec	r;
	size_t	i;
	size_t	d;
	size_t	unit;

	i = 0;
	d = 0;
	unit = calc_unit(data);
	r.x = data->game->width * 313 / WIN_WID;
	r.y = data->game->height * 182 / WIN_HEI;
	printf("(%d, %d)\n", r.x, r.y);
	//printf("%zu\n", unit);
	//map_img = mlx_new_image(data->mlx, data->game->width, data->game->height);
	p.y = (data->game->height / 2) + (data->game->height / 4);
	p.x = data->game->width / 2;
	s.x = data->game->width / 2 - r.x / 2;
	s.y = data->game->height / 2;
	printf("s (%d, %d)\n", s.x, s.y);
	e.x = data->game->width / 2 + r.x / 2;
	e.y = data->game->height;
	printf("e (%d, %d)\n", e.x, e.y);
	while (data->map[i])
	{
		while (data->map[i][d])
		{
			if (p.x >= s.x && p.x <= e.x && p.y >= s.y && p.y <= e.y)
			{
				if (data->map[i][d] == '2')
					draw_square(data->image, p, unit, 0x06FF00AA);
				if (data->map[i][d] == '3')
					draw_square(data->image, p, unit, 0x06FF0011);
				if (data->map[i][d] == '1')
					draw_square(data->image, p, unit, 0x06FF00FF);
				if (data->map[i][d] == '0')
					draw_square(data->image, p, unit, 0x000000FF);
			}
			d++;
			p.x += unit;
		}
		i++;
		p.y += unit;
		d = 0;
		p.x = data->game->width / 2;
	}
	draw_player(data->image, data->player, unit);
	//mlx_image_to_window(data->mlx, map, 0, 0);
}

