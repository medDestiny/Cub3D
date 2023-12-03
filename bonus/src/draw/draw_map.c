/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:43:57 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/03 19:08:44 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_squareline(t_data *data, t_ivec p, int size, int color, t_ivec e)
{
	int	i;
	int	j;

	i = 0;
	size -= 1;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (p.x + j < e.x && p.y + i < e.y)
				mlx_put_pixel(data->image, p.x + j, p.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_sanity_bar(t_data *data)
{
	t_fvec	s;
	t_fvec	e;
	t_fvec	d;
	t_fvec	ratio;
	int		max_sanity = SANITY;
	int		level;
	int		color;

	ratio.x = data->game->width * 115 / WIN_WID;
	ratio.y = data->game->height * 127 / WIN_HEI;

	level = (float)(data->player->sanity * ratio.y) / max_sanity;

	d.x = data->game->width * 40 / WIN_WID;
	d.y = data->game->height * 303 / WIN_HEI;

	s.x = data->game->width / 2 + d.x;
	s.y = data->game->height / 2 + d.y;

	e.x = s.x + ratio.x;
	e.y = s.y + ratio.y;
	color = 0x222222FF;
	while (s.y < e.y)
	{
		if ((int)e.y - (int)s.y <= level)
			color = 0xDD2222FF;
		draw_line(data, (t_fvec){s.x, s.y}, (t_fvec){e.x, s.y}, color);
		s.y++;
	}
}

size_t	calc_unit(t_fvec r)
{
	return (r.x / 15);
}

/*
 * calculated the ratio of the minimap area depending on the game width and height
 * calculated left and right distances from the mid of the WIDTH
 * calculated the unit depending on the minimap square (181 at first) divided by the number of squares we choose to draw
 * (181) minimap initial square unit
 * (156) left initial distance from the WIDTH / 2
 * (25) right initial distance from the WIDTH / 2
 * (250) distance from the mid of the screen and the tablet y
 */


static void	draw_map(t_data *data, t_minimap minimap)
{
	while (data->map[i])
	{
		while (data->map[i][d])
		{
			if (minimap.p.x >= minimap.s.x && minimap.p.x < minimap.e.x
					&& minimap.p.y >= minimap.s.y && minimap.p.y < minimap.e.y)
			{
				if (data->map[i][d] == '2')
					draw_squareline(data, minimap.p, minimap.unit, 0x06FF00AA, minimap.e);
				else if (data->map[i][d] == '3')
					draw_squareline(data, minimap.p, minimap.unit, 0x06FF0011, minimap.e);
				else if (data->map[i][d] == '1')
					draw_squareline(data, minimap.p, minimap.unit, 0x06FF00FF, minimap.e);
				else if (data->map[i][d] == 'a')
					draw_circle(data, (t_fvec){minimap.p.x + 5,
							minimap.p.y + 5}, minimap.unit / 3, 0x06FF00FF);
			}
			minimap.d++;
			minimap.p.x += minimap.unit;
		}
		minimap.i++;
		minimap.p.y += minimap.unit;
		minimap.d = 0;
		minimap.p.x = minimap.center.x - (data->player->pos.x / UNIT) * minimap.unit;
	}
}

static t_minimap	init_data(t_data *data)
{
	t_minimap	minimap;

	minimap.i = 0;
	minimap.d = 0;
	minimap.ratio.x = data->game->width * 181 / WIN_WID;
	minimap.ratio.y = data->game->height * 181 / WIN_HEI;

	minimap.left = data->game->width * 156 / WIN_WID;
	minimap.right = data->game->width * 25 / WIN_WID;

	minimap.y_rat = data->game->height * 250 / WIN_HEI;
	minimap.unit = calc_unit(ratio);
	minimap.s.x = data->game->width / 2 - left;
	minimap.s.y = data->game->height / 2 + y_rat;


	minimap.center.x = minimap.s.x + minimap.ratio.x / 2;
	minimap.center.y = minimap.s.y + minimap.ratio.y / 2;

	minimap.p.x = minimap.center.x - (data->player->pos.x / UNIT) * minimap.unit;
	minimap.p.y = minimap.center.y - (data->player->pos.y / UNIT) * minimap.unit;

	minimap.e.x = data->game->width / 2 + minimap.right;
	minimap.e.y = data->game->height / 2 + minimap.y_rat + minimap.ratio.y;
	return (minimap);
}

void	draw_tablet(t_data *data)
{
	t_minimap	minimap;

	map_info = init_data(data);
	draw_map(data, minimap);
	draw_circle(data, minimap.center,
			minimap.unit / 4, 0xFF0000FF);
	draw_sanity_bar(data);
}
