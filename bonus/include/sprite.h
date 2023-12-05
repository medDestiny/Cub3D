/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 16:23:51 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/05 12:20:44 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "vectors.h"

# define ACTIVE 1
# define INACTIVE 0

typedef struct s_data	t_data;
typedef struct s_stripe	t_stripe;

typedef struct s_sprite
{
	short int		state;
	t_fvec			pos;
	mlx_texture_t	**texture;
	double			time;
	unsigned int	tex_max;
	unsigned int	tex_index;
}	t_sprite;

typedef struct s_sp_list
{
	t_sprite			*sp;
	struct s_sp_list	*next;
}	t_sp_list;

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
void	sp_draw_stripe(t_data *data, mlx_texture_t *tex, t_stripe stripe,
			float dist);
void	sp_draw_stripes(t_data *data, t_sprite *sp, t_sp_data *sp_data);
void	sp_stripe_data(t_stripe *s, t_data *data, t_sp_data *sp_data);
void	sp_get_data(t_data *data, t_sprite *sp, t_sp_data *sp_data);

float	get_angle_diff(float pa, float alpha);
float	get_sprite_angle(t_fvec diff);

#endif
