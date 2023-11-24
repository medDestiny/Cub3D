/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:38:37 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/24 10:29:48 by mmisskin         ###   ########.fr       */
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

void	sp_stripe_data(t_stripe *s, t_data *data, t_sp_data *sp_data)
{
	s->draw_s = data->game.height / 2 - sp_data->size / 2;
	s->draw_e = data->game.height / 2 + sp_data->size / 2;
	s->yoffset = 0;
	if (s->draw_s < 0)
		s->draw_s = 0;
	if (s->draw_e >= (int)data->game.height)
	{
		if (s->draw_e > (int)data->game.height)
			s->yoffset = (s->draw_e - data->game.height) * s->y_step;
		s->draw_e = data->game.height - 1;
	}
}

void	sp_draw_stripe(t_data *data, mlx_texture_t *tex, t_stripe s)
{
	size_t		index;
	uint32_t	color;
	uint32_t	*texture;

	texture = (uint32_t *)tex->pixels;
	if (s.pos >= (int)data->game.width)
		return ;
	while (s.draw_s < s.draw_e)
	{
		index = (int)s.xoffset + tex->width * (int)s.yoffset;
		if (index >= tex->width * tex->height)
			break ;
		color = rev_bits(texture[index]);
		if ((color << 24) != 0)
			mlx_put_pixel(data->image_p, s.pos, s.draw_s, color);
		s.yoffset += s.y_step;
		s.draw_s++;
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
		if (start >= 0 && start < (int)data->game.width
			&& sp_data->distance < data->zbuffer[start])
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

void	draw_ceiling(t_data *data, int x, int end, uint32_t color)
{
	int	y;

	y = 0;
	while (y < end)
	{
		mlx_put_pixel(data->image_p, x, y, color);
		y++;
	}
}

void	draw_floor(t_data *data, int x, int start, uint32_t color)
{
	int	y;

	y = start;
	while (y < (int)data->game.height)
	{
		mlx_put_pixel(data->image_p, x, y, color);
		y++;
	}
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

void	draw_hud(t_data *data)
{
	t_ivec		pos;
	t_fvec		step;
	t_fvec		offset;
	uint32_t	color;
	uint32_t	*texture;

	texture = (uint32_t *)h->pixels;
	step.x = (float)h->width / data->game.width;
	step.y = (float)h->height / data->game.height;
	pos.x = -1;
	offset.x = 0;
	while (++pos.x < (int)data->game.width)
	{
		pos.y = -1;
		offset.y = 0;
		while (++pos.y < (int)data->game.height)
		{
			color = rev_bits(texture[(int)offset.x + (int)offset.y * h->width]);
			if ((color << 24) != 0)
				mlx_put_pixel(data->image_p, pos.x, pos.y, color);
			offset.y += step.y;
		}
		offset.x += step.x;
	}
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
	unsigned int	pos;
	t_ray			r;

	r.distance = 0;
	r.angle = fix_angle(data->player->angle - ((FOV / 2) * M_PI / 180));
	pos = -1;
	while (++pos < data->game.width)
	{
		get_dir_vector(&r.dir.x, &r.dir.y, r.angle);
		r.delta.x = sqrt(1 + (r.dir.y * r.dir.y) / (r.dir.x * r.dir.x));
		r.delta.y = sqrt(1 + (r.dir.x * r.dir.x) / (r.dir.y * r.dir.y));
		r.map.x = data->player->pos.x / UNIT;
		r.map.y = data->player->pos.y / UNIT;
		set_initial_intersect(&r, data->player->pos);
		cast_ray(data, &r, pos);
		r.angle = fix_angle(r.angle + (FOV * M_PI / 180) / data->game.width);
	}
}
