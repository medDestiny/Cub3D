/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:38:37 by mmisskin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/11/02 16:51:50 by mmisskin         ###   ########.fr       */
=======
/*   Updated: 2023/11/06 16:07:21 by mmisskin         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

uint32_t	rev_bits(uint32_t color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	a = (color >> 24) & 0xFF;
	b = (color >> 8) & 0xFF00;
	g = (color << 8) & 0xFF0000;
	r = (color << 24) & 0xFF000000;
	return (r | g | b | a);
}

<<<<<<< HEAD
void	draw_stripe(mlx_image_t *image, t_player *p, t_ray *ray, int pos, int side)
=======
void	draw_stripe(mlx_image_t *image, t_player *p, t_ray *ray, int pos, int side, char **map)
>>>>>>> main
{
	int	height;
	float	draw_s;
	float	draw_e;
	int	color;
	float	xoffset;
<<<<<<< HEAD
	t_fvec	r;

=======
	mlx_texture_t	*tex;
	t_fvec	r;

	if (map[ray->map.y][ray->map.x] == '1')
		tex = t;
	else
		tex = d;
>>>>>>> main
	r.x = p->pos.x + (ray->dir.x * ray->distance);
	r.y = p->pos.y + (ray->dir.y * ray->distance);
	ray->distance *= cos(p->angle - ray->angle);
	height = UNIT / ray->distance * WIN_HEI;
	float next_pixel = 0;
	float step = (float)tex->height / height;
	draw_s =  WIN_HEI / 2 - height / 2;
	if (draw_s < 0)
		draw_s = 0;
	draw_e = height / 2 + WIN_HEI / 2;
	if (draw_e >= WIN_HEI)
	{
		if (draw_e > WIN_HEI)
			next_pixel = (draw_e - WIN_HEI) * step;
		draw_e = WIN_HEI - 1;
	}
	if (side == 0)
		xoffset = (int)r.y % UNIT; // point of intersection in the unit
	else
		xoffset = (int)r.x % UNIT; // point of intersection in the unit
<<<<<<< HEAD
	uint32_t	*texture = (uint32_t *)tex->pixels;
=======
	uint32_t	*texture;
	texture = (uint32_t *)tex->pixels;
>>>>>>> main
	int x = (xoffset * tex->width / UNIT);
	uint32_t	dcolor;
	while (draw_s < draw_e)
	{
		dcolor = rev_bits(texture[(x + tex->width * (int)next_pixel)]);
		mlx_put_pixel(image, pos, draw_s, dcolor);
		next_pixel += step;
		draw_s++;
	}
	(void)color;
	(void)side;
	(void)pos;
	color = 0xFF0000FF;
	// draw_line(image, (t_fvec){pos, draw_s}, (t_fvec){pos, draw_e}, color);
	//draw_line(image, p->pos, r, color);
}

void	cast_ray(t_data *data, t_ray *ray, int pos)
{
	int		wall;
	int		side;

	wall = 0;
	ray->distance = 0;
	while (!wall && ray->distance < DOF)
	{
		if (ray->len.x < ray->len.y)
		{
			ray->map.x += ray->step.x;
			ray->distance = ray->len.x;
			ray->len.x += ray->delta.x * UNIT;
			side = 0;
		}
		else
		{
			ray->map.y += ray->step.y;
			ray->distance = ray->len.y;
			ray->len.y += ray->delta.y * UNIT;
			side = 1;
		}
		if (data->map[ray->map.y] && is_wall(data->map[ray->map.y][ray->map.x]))
			wall = 1;
	}
	if (wall)
		draw_stripe(data->image_p, data->player, ray, pos, side, data->map);
}

void	draw_scene(t_data *data)
{
	int		pos;
	t_ray	ray;

	pos = 0;
	ray.angle = data->player->angle - ((FOV / 2) * M_PI / 180);
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	else if (ray.angle > 2 * M_PI)
		ray.angle -= 2 * M_PI;
	while (pos < WIN_WID)
	{
		get_dir_vector(&ray.dir.x, &ray.dir.y, ray.angle);
		ray.delta.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
		ray.delta.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
		ray.map.x = data->player->pos.x / UNIT;
		ray.map.y = data->player->pos.y / UNIT;
		set_initial_intersect(&ray, data->player->pos);
		cast_ray(data, &ray, pos);
		ray.angle += (FOV * M_PI / 180) / WIN_WID;
		pos++;
	}
}
