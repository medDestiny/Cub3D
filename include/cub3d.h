/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:56:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/22 20:48:07 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "map.h"
# include "astar.h"
# include "vectors.h"
# include "parser.h"
# include "sprite.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_WID 1280
# define WIN_HEI 960
# define UNIT 3000
# define SPEED UNIT / 10 * 0.5
# define FOV 60
# define DOF 1000 * UNIT

extern mlx_texture_t *tex;

typedef struct s_mvm
{
	short int	front;
	short int	back;
	short int	left;
	short int	right;
}	t_mvm;

typedef struct s_player
{
	t_fvec	pos;
	t_fvec	dir;
	t_mvm	move;
	float	angle;
}	t_player;

typedef struct s_lst
{
	t_node			*node;
	struct s_lst	*next;
}	t_lst;

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
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*image_p;
	char		**map;
	float		*zbuffer;
	t_sprite	*enemy;
	t_player	*player;
	t_astar		*astar;
	t_game		game;
	mlx_texture_t	*textures[4];
	uint32_t		floor_color;
	uint32_t		cieling_color;
	int				floor_flag;
	int				cieling_flag;
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

mlx_texture_t *t;
mlx_texture_t *d;
mlx_texture_t *tex;
mlx_texture_t *spr[5];

void	get_dir_vector(float *x, float *y, float angle);

//		Drawing functions
void	draw_player(mlx_image_t *image, t_player *player);
void	draw_circle(mlx_image_t *image, t_fvec c, int rad, int color);
void	draw_map(mlx_image_t *img, char **map);
void	draw_square(mlx_image_t *image, t_ivec p, int size, int color);
void	draw_line(mlx_image_t *image, t_fvec p1, t_fvec p2, int color);
void	draw_scene(t_data *data);

//		Ray Casting function
void	cast_ray(t_data *data, t_ray *ray, int pos);

//		Checking for walls
int		is_wall(char pos);

#endif
