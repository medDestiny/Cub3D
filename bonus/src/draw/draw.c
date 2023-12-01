/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:55:19 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 14:44:48 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_line(mlx_image_t *image, t_fvec p1, t_fvec p2, int color)
{
	int		i;
	int		step;
	t_ivec	delta;
	t_fvec	inc;

	i = 0;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	if (abs(delta.x) > abs(delta.y))
		step = abs(delta.x);
	else
		step = abs(delta.y);
	inc.x = delta.x / (float)step;
	inc.y = delta.y / (float)step;
	while (i <= step)
	{
		if (p1.x >= WIN_WID || p1.y >= WIN_HEI || p1.x < 0 || p1.y < 0)
			break ;
		mlx_put_pixel(image, p1.x, p1.y, color);
		p1.x += inc.x;
		p1.y += inc.y;
		i++;
	}
}

void	draw_square(mlx_image_t *image, t_ivec p, int size, int color)
{
	int	i;

	i = 0;
	size -= 1;
	(void)color;
	while (i <= size)
	{
		draw_line(image, (t_fvec){p.x, p.y + i}, (t_fvec){p.x + size, p.y + i}, color);
		i++;
	}
}

void	draw_circle(mlx_image_t *image, t_fvec c, int rad, int color)
{
	int	x;
	int	y;

	x = -rad;
	while (x <= rad)
	{
		y = -rad;
		while (y <= rad)
		{
			if (x * x + y * y < rad * rad)
				if (c.x + x <= WIN_WID && c.y + y <= WIN_HEI && c.x + x > 0 && c.y + y > 0)
					mlx_put_pixel(image, c.x + x, c.y + y, color);
			y++;
		}
		x++;
	}
}

void	draw_player(mlx_image_t *image, t_player *player, size_t unit)
{
	t_fvec	p;

	t_fvec	pos;
	(void)unit;
	pos.x = (player->pos.x / 10) * 20;
	pos.y = (player->pos.y / 10) * 20;
	get_dir_vector(&p.x, &p.y, player->angle);
	p.x = player->dir.x * 10 + pos.x;
	p.y = player->dir.y * 10 + pos.y;
	draw_circle(image, pos, 5, 0xFF0000FF);
	draw_line(image, pos, p, 0xFF0000FF);
}
