/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:55:19 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/06 10:16:08 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_line(t_data *data, t_fvec p1, t_fvec p2, int color)
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
		if (p1.x >= data->game->width
			|| p1.y >= data->game->height || p1.x < 0 || p1.y < 0)
			break ;
		mlx_put_pixel(data->image, p1.x, p1.y, color);
		p1.x += inc.x;
		p1.y += inc.y;
		i++;
	}
}

void	draw_squareline(t_data *data, t_minimap m, int color)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = m.unit - 1;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (m.p.x + j < m.e.x && m.p.y + i < m.e.y)
				mlx_put_pixel(data->image, m.p.x + j, m.p.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_square(t_data *data, t_ivec p, int size, int color)
{
	int	i;

	i = 0;
	size -= 1;
	while (i <= size)
	{
		draw_line(data, (t_fvec){p.x, p.y + i},
			(t_fvec){p.x + size, p.y + i}, color);
		i++;
	}
}

void	draw_circle(t_data *data, t_fvec c, int rad, int color)
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
				if (c.x + x <= data->game->width
					&& c.y + y <= data->game->height
					&& c.x + x > 0 && c.y + y > 0)
					mlx_put_pixel(data->image, c.x + x, c.y + y, color);
			y++;
		}
		x++;
	}
}

void	draw_player(t_data *data, t_fvec pos, size_t unit)
{
	t_fvec	p;

	get_dir_vector(&p.x, &p.y, data->player->angle);
	p.x = data->player->dir.x * (unit * 2.5) + pos.x;
	p.y = data->player->dir.y * (unit * 2.5) + pos.y;
	draw_circle(data, pos, unit, 0xe4e6a8FF);
	draw_line(data, pos, p, 0xe4e6a8FF);
}
