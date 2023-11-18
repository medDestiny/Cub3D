/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:38:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/18 21:48:40 by mmisskin         ###   ########.fr       */
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

float	get_sprite_angle(t_fvec diff)
{
	float	alpha;

	alpha = atan2(diff.y, diff.x);
	if (alpha > 2 * M_PI)
		alpha -= 2 * M_PI;
	else if (alpha < 0)
		alpha += 2 * M_PI;
	return (alpha);
}

float	get_angle_diff(float pa, float alpha)
{
	float	diff;

	diff = pa - alpha;
	if (pa > 3 * M_PI / 2 && alpha < M_PI / 2)
		diff -= 2 * M_PI;
	else if (pa < M_PI / 2 && alpha > 3 * M_PI / 2)
		diff += 2 * M_PI;
	return (diff);
}

void	sp_get_data(t_data *data, t_sp_data *sp_data)
{
	t_fvec	diff;
	float	alpha;
	float	sa;
	float	scr_angle;
	float	ratio;

	diff.x = data->enemy->pos.x - data->player->pos.x;
	diff.y = data->enemy->pos.y - data->player->pos.y;
	alpha = get_sprite_angle(diff);
	sp_data->distance = sqrt(diff.x * diff.x + diff.y * diff.y);
	if (sp_data->distance == 0) // to not divide by 0
		sp_data->distance = 1;
	sp_data->size = (float)(data->game.height * UNIT) / sp_data->distance;
	sa = get_angle_diff(data->player->angle, alpha);
	scr_angle = (FOV / 2) - (sa * 180 / M_PI);
	ratio = (float)data->game.width / FOV;
	sp_data->x = scr_angle * ratio;
}

void	sp_stripe_data(t_stripe *stripe, t_data *data, t_sp_data *sp_data)
{
	stripe->draw_s = data->game.height / 2 - sp_data->size / 2;
	stripe->draw_e = data->game.height / 2 + sp_data->size / 2;
	stripe->yoffset = 0;
	if (stripe->draw_s < 0)
		stripe->draw_s = 0;
	if (stripe->draw_e >= (int)data->game.height)
	{
		if (stripe->draw_e > (int)data->game.height)
			stripe->yoffset = (stripe->draw_e - data->game.height) * stripe->y_step;
		stripe->draw_e = data->game.height - 1;
	}
}

void	sp_draw_stripe(t_data *data, mlx_texture_t *tex, t_stripe stripe)
{
	uint32_t	color;
	uint32_t	*texture;

	texture = (uint32_t *)tex->pixels;
	if (stripe.pos >= (int)data->game.width)
		return ;
	while (stripe.draw_s < stripe.draw_e)
	{
		if ((int)stripe.xoffset + tex->width * (int)stripe.yoffset >= tex->width * tex->height)
			break ;
		color = rev_bits(texture[(int)stripe.xoffset + tex->width * (int)stripe.yoffset]);
		if ((color << 24) != 0)
			mlx_put_pixel(data->image_p, stripe.pos, stripe.draw_s, color);
		stripe.yoffset += stripe.y_step;
		stripe.draw_s++;
	}
}

void	set_timer(int *timer, int *var, int var_max, int delay)
{
	if (*timer >= delay)
	{
		*timer = 0;
		*var += 1;
	}
	if (*var == var_max)
		*var = 0;
	*timer += 1;
}

void	sp_draw_stripes(t_data *data, t_sprite *sp, t_sp_data *sp_data)
{
	int			start;
	t_stripe	stripe;
	static int	tex_index;
	static int	timer;

	stripe.xoffset = 0;
	start = sp_data->x - sp_data->size / 2;
	stripe.x_step = (float)sp->texture[tex_index]->width / sp_data->size;
	stripe.y_step = (float)sp->texture[tex_index]->height / sp_data->size;
	while (start < sp_data->x + sp_data->size / 2)
	{
		stripe.pos = start;
		if (start >= 0 && start < (int)data->game.width && sp_data->distance < data->zbuffer[start])
		{
			sp_stripe_data(&stripe, data, sp_data);
			sp_draw_stripe(data, sp->texture[tex_index], stripe);
		}
		stripe.xoffset += stripe.x_step;
		start++;
	}
	set_timer(&timer, &tex_index, 5, 3);
}

void	draw_sprite(t_data *data, t_sprite *sp)
{
	t_sp_data	sp_data;

	sp_get_data(data, &sp_data);
	sp_draw_stripes(data, sp, &sp_data);
}

t_stripe	get_stripe_data(t_data *data, mlx_texture_t *tex, int height)
{
	t_stripe	stripe;

	printf("gh = %d\n", data->game.height);
	printf("h = %d\n", height);
	stripe.draw_s = data->game.height / 2 - height / 2;
	stripe.draw_e = data->game.height / 2 + height / 2;
	stripe.y_step = (float)tex->height / height;
	stripe.yoffset = 0;
	if (stripe.draw_s < 0)
		stripe.draw_s = 0;
	if (stripe.draw_e >= (int)data->game.height)
	{
		if (stripe.draw_e > (int)data->game.height)
			stripe.yoffset = (stripe.draw_e - data->game.height) * stripe.y_step;
		stripe.draw_e = data->game.height - 1;
	}
	return (stripe);
}

void	draw_stripe(t_data *data, t_player *p, t_ray *ray, int pos, int side, char **map)
{
	t_stripe	s;
	uint32_t	*texture;
	int	height;
	float	xoffset;
	mlx_texture_t	*tex;
	t_fvec	r;
	uint32_t	color;

	if (map[ray->map.y][ray->map.x] == '1')
		tex = t;
	else
		tex = d;
	r.x = p->pos.x + (ray->dir.x * ray->distance);
	r.y = p->pos.y + (ray->dir.y * ray->distance);
	data->zbuffer[pos] = ray->distance;
	ray->distance *= cos(p->angle - ray->angle);
	if (ray->distance == 0) // temporarly
		ray->distance = 1;
	height = UNIT / ray->distance * data->game.height;
	s = get_stripe_data(data, tex, height);
	if (side == 0)
		xoffset = (int)r.y % UNIT; // point of intersection in the unit
	else
		xoffset = (int)r.x % UNIT; // point of intersection in the unit
	texture = (uint32_t *)tex->pixels;
	s.xoffset = xoffset * tex->width / UNIT;
	printf("(%d, %d)\n", s.draw_s, s.draw_e);
	while (s.draw_s < s.draw_e)
	{
		color = rev_bits(texture[(int)s.xoffset + tex->width * (int)s.yoffset]);
		mlx_put_pixel(data->image_p, pos, s.draw_s, color);
		s.yoffset += s.y_step;
		s.draw_s++;
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
		draw_stripe(data, data->player, ray, pos, side, data->map);
}

void	draw_scene(t_data *data)
{
	unsigned int	pos;
	t_ray			ray;

	pos = 0;
	ray.distance = 0;
	ray.angle = data->player->angle - ((FOV / 2) * M_PI / 180);
	if (ray.angle < 0)
		ray.angle += 2 * M_PI;
	else if (ray.angle > 2 * M_PI)
		ray.angle -= 2 * M_PI;
	while (pos < data->game.width)
	{
		get_dir_vector(&ray.dir.x, &ray.dir.y, ray.angle);
		ray.delta.x = sqrt(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
		ray.delta.y = sqrt(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
		ray.map.x = data->player->pos.x / UNIT;
		ray.map.y = data->player->pos.y / UNIT;
		set_initial_intersect(&ray, data->player->pos);
		cast_ray(data, &ray, pos);
		ray.angle += (FOV * M_PI / 180) / data->game.width;
		pos++;
	}
}
