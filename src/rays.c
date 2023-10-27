/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:38:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/27 23:02:21 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t *tex;

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

void	draw_stripe(mlx_image_t *image, t_player *p, t_ray *ray, int pos, int side)
{
	int	height;
	int	draw_s;
	int	draw_e;
	int	color;
	int	xoffset;
	t_fvec	r;

	ray->distance *= cos(p->angle - ray->angle);
	r.x = p->pos.x + (ray->dir.x * ray->distance);
	r.y = p->pos.y + (ray->dir.y * ray->distance);
	printf("%f\t%f\n", r.x, r.y);
	height = WIN_HEI / (ray->distance / 10);
	draw_s = -height / 2 + WIN_HEI / 2;
	if (draw_s < 0)
		draw_s = 0;
	draw_e = height / 2 + WIN_HEI / 2;
	if (draw_e >= WIN_HEI)
		draw_e = WIN_HEI - 1;
	// if (side == 1)
	// 	color = 0x7A0808FF;
	// else
	// 	color = 0x5E060FFF;
	// if (side == 0)
	// 	xoffset = (int)(p->pos.y + (ray->dir.y * ray->distance)) % UNIT; // point of intersection in the unit
	// else
	// 	xoffset = (int)(p->pos.x + (ray->dir.x * ray->distance)) % UNIT;
	if (side == 0)
		xoffset = r.y - (int)(r.y / UNIT) * UNIT; // point of intersection in the unit
	else
		xoffset = r.x - (int)(r.x / UNIT) * UNIT; // point of intersection in the unit
	printf("%d\n", xoffset);
	int x = xoffset * tex->width / UNIT;
	int v = UNIT / tex->width;
	int dcolor;
	while (draw_s < draw_e)
	{
		dcolor = tex->pixels[x] << 24 | tex->pixels[x + 1] << 16 | tex->pixels[x + 2] << 8 | tex->pixels[x + 3];	
		mlx_put_pixel(image, pos, draw_s, dcolor);
		x += tex->width * floor(v);
		v += v;
		draw_s++;
	}
	(void)color;
	// draw_line(image, (t_fvec){pos, draw_s}, (t_fvec){pos, draw_e}, color);
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
		if (data->map[ray->map.y] && data->map[ray->map.y][ray->map.x] == '1')
			wall = 1;
	}
	if (wall)
		draw_stripe(data->image_p, data->player, ray, pos, side);
}

void	draw_scene(t_data *data)
{
	int		pos;
	t_ray	ray;
	tex =  mlx_load_png("../texture.png");

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
