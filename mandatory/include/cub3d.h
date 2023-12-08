/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:56:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/08 01:42:42 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include "vectors.h"
# include "parser.h"
# include "player.h"
# include <math.h>
# include <stdlib.h>

# define WIN_WID 1280
# define WIN_HEI 960
# define UNIT 300
# define FOV 60
# define DOF 100000000000

# define HORI_WALL 1
# define VERT_WALL 0

typedef struct s_game
{
	unsigned int	height;
	unsigned int	width;
}	t_game;

typedef struct s_stripe
{
	int			pos;
	int			draw_s;
	int			draw_e;
	float		x_step;
	float		y_step;
	float		xoffset;
	float		yoffset;
}	t_stripe;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	char			**map;
	t_player		*player;
	t_game			game;
	mlx_texture_t	*textures[4];
	long			floor_color;
	long			ceiling_color;
}	t_data;

typedef struct s_ray
{
	t_fvec	dir;
	t_fvec	delta;
	t_fvec	len;
	t_ivec	map;
	t_ivec	step;
	float	distance;
	float	angle;
}	t_ray;

//			Drawing functions
void		draw_scene(t_data *data);
void		draw_ceiling(t_data *data, int x, int end, uint32_t color);
void		draw_floor(t_data *data, int x, int start, uint32_t color);
void		draw_stripe(t_data *data, t_ray *ray, int pos, int side);

//			Input registration
void		player_hooks(mlx_key_data_t keydata, t_data *data);
void		key_hooks(mlx_key_data_t keydata, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		close_hook(void *param);
void		hooks(void *param);

//			Ray Casting function
void		cast_ray(t_data *data, t_ray *ray, int pos);

//			Checking for walls
int			is_wall(char pos);

//			Gets direction vector
void		get_dir_vector(float *x, float *y, float angle);

//			Reverse texture->pixels bits (abgr -> rgba)
uint32_t	rev_bits(uint32_t color);

//			Keeps the angle in range of [0, 2 * PI]
float		fix_angle(float angle);

//			Memory management
void		*ft_malloc(size_t size, t_data *data);
void		clean_all(t_data *data);
void		clean_vec(char **vec);

#endif
