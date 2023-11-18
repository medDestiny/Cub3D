/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:23:51 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/18 18:43:55 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "vectors.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_data	t_data;
typedef struct s_stripe	t_stripe;

typedef struct s_sprite
{
	t_fvec			pos;
//	mlx_texture_t	**texture;
	mlx_texture_t	*texture[5]; // temporarly
	unsigned int	tex_max;
}	t_sprite;

typedef struct s_sp_data
{
	int	x;
	int	size;
	int	distance;
}	t_sp_data;

/*
 *	Functions responsible for drawing and animating sprites
 */

void	draw_sprite(t_data *data, t_sprite *sp);

void	sp_draw_stripe(t_data *data, mlx_texture_t *tex, t_stripe stripe);
void	sp_draw_stripes(t_data *data, t_sprite *sp, t_sp_data *sp_data);

#endif
