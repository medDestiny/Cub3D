/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:33:58 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:36:59 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	sp_draw_stripes(t_data *data, t_sprite *sp, t_sp_data *sp_data)
{
	int			start;
	t_stripe	stripe;
	static int	tex_index;
	//static int	timer;

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
	//set_timer(&timer, &tex_index, 5, 3);
}

void	draw_sprite(t_data *data, t_sprite *sp)
{
	t_sp_data	sp_data;

	sp_get_data(data, &sp_data);
	sp_draw_stripes(data, sp, &sp_data);
}

