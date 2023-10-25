/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:55:19 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/25 12:00:59 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	while (i <= size)
	{
		draw_line(image, (t_fvec){p.x, p.y + i}, (t_fvec){p.x + size, p.y + i}, color);
		i++;
	}
	//draw_line(image, (t_fvec){p.x, p.y}, (t_fvec){p.x + size, p.y}, 0xFFFFFFFF);
	//draw_line(image, (t_fvec){p.x, p.y}, (t_fvec){p.x, p.y + size}, 0xFFFFFFFF);
	//draw_line(image, (t_fvec){p.x + size, p.y}, (t_fvec){p.x + size, p.y + size}, 0xFFFFFFFF);
	//draw_line(image, (t_fvec){p.x, p.y + size}, (t_fvec){p.x + size, p.y + size}, 0xFFFFFFFF);
}

void	draw_map(mlx_image_t *img, char **map)
{
	int		i;
	int		j;
	size_t	size;

	size = 0;
	while (map[size])
		size++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, (t_ivec){j * UNIT, i * UNIT}, UNIT, 0x111111FF);
			else
				draw_square(img, (t_ivec){j * UNIT, i * UNIT}, UNIT, 0x222222FF);
			j++;
		}
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

void	draw_player(mlx_image_t *image, t_player *player)
{
	t_fvec	p;

	get_dir_vector(&p.x, &p.y, player->angle);
	p.x = player->dir.x * 10 + player->pos.x;
	p.y = player->dir.y * 10 + player->pos.y;
	draw_circle(image, player->pos, 5, 0xFF0000FF);
	draw_line(image, player->pos, p, 0xFF0000FF);
}
