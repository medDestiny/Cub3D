/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:43:57 by anchaouk          #+#    #+#             */
/*   Updated: 2023/12/02 20:05:00 by anchaouk         ###   ########.fr       */
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
	//draw_square(data, s, ratio.y, 0xFF2222FF);
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

void	draw_map(t_data *data)
{
	//mlx_image_t	*map_img;
	t_ivec	p;
	t_ivec	s;
	t_ivec	e;
	t_fvec	ratio;
	t_fvec	center;
	float	left;
	float	right;
	float	y_rat;
	size_t	i;
	size_t	d;
	size_t	unit;

	i = 0;
	ratio.x = data->game->width * 181 / WIN_WID;
	ratio.y = data->game->height * 181 / WIN_HEI;

	left = data->game->width * 156 / WIN_WID;
	right = data->game->width * 25 / WIN_WID;

	y_rat = data->game->height * 250 / WIN_HEI;
	//printf("(%.0f, %.0f)\n", ratio.x, ratio.y);
	unit = calc_unit(ratio);
	//printf("%zu\n", unit);
	//map_img = mlx_new_image(data->mlx, data->game->width, data->game->height);
	//p.y = (data->game->height / 2) + (data->game->height / 4);
	//p.x = data->game->width / 2;
	s.x = data->game->width / 2 - left;
	s.y = data->game->height / 2 + y_rat;

	//printf("s (%d, %d)\n", s.x, s.y);

	center.x = s.x + ratio.x / 2;
	center.y = s.y + ratio.y / 2;

	p.x = center.x - (data->player->pos.x / UNIT) * unit;
	p.y = center.y - (data->player->pos.y / UNIT) * unit;
	//printf("p (%d, %d)\n", p.x, p.y);

	e.x = data->game->width / 2 + right;
	e.y = data->game->height / 2 + y_rat + ratio.y;
	//printf("e (%d, %d)\n", e.x, e.y);
	//draw_square(data, s, unit * 16, 0x222222FF);
	while (data->map[i])
	{
		while (data->map[i][d])
		{
			if (p.x >= s.x && p.x < e.x && p.y >= s.y && p.y < e.y)
			{
				if (data->map[i][d] == '2')
					draw_squareline(data, p, unit, 0x06FF00AA, e);
				else if (data->map[i][d] == '3')
					draw_squareline(data, p, unit, 0x06FF0011, e);
				else if (data->map[i][d] == '1')
					draw_squareline(data, p, unit, 0x06FF00FF, e);
				else if (data->map[i][d] == 'a')
					draw_circle(data, (t_fvec){p.x + 5, p.y + 5}, unit / 3, 0x06FF00FF);
				//else if (data->map[i][d] == '0' || data->map[i][d] == 'a')
				//	draw_square(data, p, unit, 0x000000FF);
			}
			d++;
			p.x += unit;
		}
		i++;
		p.y += unit;
		d = 0;
		p.x = center.x - (data->player->pos.x / UNIT) * unit;
	}
	draw_circle(data, center, unit / 4, 0xFF0000FF);
	//mlx_image_to_window(data->mlx, map, 0, 0);
	draw_sanity_bar(data); // tmp
	(void)color;
	(void)color;
}
