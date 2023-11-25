/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stripe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:43:45 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:44:31 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_stripe	get_stripe_data(t_data *data, mlx_texture_t *tex, int height)
{
	t_stripe	s;

	s.draw_s = data->game.height / 2 - height / 2;
	s.draw_e = data->game.height / 2 + height / 2;
	s.y_step = (float)tex->height / height;
	s.yoffset = 0;
	if (s.draw_s < 0)
		s.draw_s = 0;
	if (s.draw_e >= (int)data->game.height)
	{
		if (s.draw_e > (int)data->game.height)
			s.yoffset = (s.draw_e - data->game.height) * s.y_step;
		s.draw_e = data->game.height - 1;
	}
	return (s);
}

void	draw_textured_stripe(t_data *data, t_stripe s, mlx_texture_t *tex)
{
	uint32_t	color;
	uint32_t	*texture;

	texture = (uint32_t *)tex->pixels;
	draw_ceiling(data, s.pos, s.draw_s, data->ceiling_color);
	draw_floor(data, s.pos, s.draw_e, data->floor_color);
	while (s.draw_s < s.draw_e)
	{
		color = rev_bits(texture[(int)s.xoffset + tex->width * (int)s.yoffset]);
		mlx_put_pixel(data->image_p, s.pos, s.draw_s, color);
		s.yoffset += s.y_step;
		s.draw_s++;
	}
}

mlx_texture_t	*choose_texture(t_data *data, t_ray *ray, int side)
{
	mlx_texture_t	*t;

	if (data->map[ray->map.y][ray->map.x] == '2')
		return (d);
	if (ray->angle > M_PI && side == HORI_WALL)
		t = data->textures[NO];
	else if (ray->angle <= M_PI && side == HORI_WALL)
		t = data->textures[SO];
	else if (ray->angle > M_PI / 2 && ray->angle <= 3 * M_PI / 2
		&& side == VERT_WALL)
		t = data->textures[WE];
	else
		t = data->textures[EA];
	return (t);
}

void	draw_stripe(t_data *data, t_ray *ray, int pos, int side)
{
	t_stripe		s;
	mlx_texture_t	*tex;
	t_fvec			intersec;
	int				height;
	float			xoffset;

	tex = choose_texture(data, ray, side);
	intersec.x = data->player->pos.x + (ray->dir.x * ray->distance);
	intersec.y = data->player->pos.y + (ray->dir.y * ray->distance);
	data->zbuffer[pos] = ray->distance;
	ray->distance *= cos(data->player->angle - ray->angle);
	if (ray->distance < 1) // temporarly
		ray->distance = 1;
	height = UNIT / ray->distance * data->game.height;
	s = get_stripe_data(data, tex, height);
	if (side == VERT_WALL)
		xoffset = (int)intersec.y % UNIT; // point of intersection in the unit
	else
		xoffset = (int)intersec.x % UNIT; // point of intersection in the unit
	s.xoffset = xoffset * tex->width / UNIT;
	s.pos = pos;
	draw_textured_stripe(data, s, tex);
}
