/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:38:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/05 17:30:00 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_initial_intersect(t_ray *ray, t_fvec pos)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->len.x = (pos.x - (float)ray->map.x * UNIT) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->len.x = ((float)(ray->map.x + 1) * UNIT - pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->len.y = (pos.y - (float)ray->map.y * UNIT) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->len.y = ((float)(ray->map.y + 1) * UNIT - pos.y) * ray->delta.y;
	}
}

void	cast_ray(t_data *data, t_ray *ray, int pos)
{
	int		wall;
	int		side;

	wall = 0;
	while (!wall && ray->distance < DOF)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->map.x += ray->step.x;
			ray->distance = ray->len.x;
			ray->len.x += ray->delta.x * UNIT;
			side = VERT_WALL;
		}
		else
		{
			ray->map.y += ray->step.y;
			ray->distance = ray->len.y;
			ray->len.y += ray->delta.y * UNIT;
			side = HORI_WALL;
		}
		if (data->map[ray->map.y] && is_wall(data->map[ray->map.y][ray->map.x]))
			wall = 1;
	}
	if (wall)
		draw_stripe(data, ray, pos, side);
}

void	draw_scene(t_data *data)
{
	int		pos;
	t_ray	r;

	r.distance = 0;
	r.angle = fix_angle(data->player->angle - ((FOV / 2) * M_PI / 180));
	pos = -1;
	while (++pos < (int)data->game->width)
	{
		get_dir_vector(&r.dir.x, &r.dir.y, r.angle);
		r.delta.x = sqrt(1 + (r.dir.y * r.dir.y) / (r.dir.x * r.dir.x));
		r.delta.y = sqrt(1 + (r.dir.x * r.dir.x) / (r.dir.y * r.dir.y));
		r.map.x = data->player->pos.x / UNIT;
		r.map.y = data->player->pos.y / UNIT;
		set_initial_intersect(&r, data->player->pos);
		cast_ray(data, &r, pos);
		r.angle = fix_angle(r.angle + (FOV * M_PI / 180) / data->game->width);
	}
}
