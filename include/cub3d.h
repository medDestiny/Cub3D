/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:56:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/27 15:37:31 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "map.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_WID 1280
# define WIN_HEI 960
# define UNIT 25
# define SPEED 0.5
# define FOV 60
# define DOF 1000
extern mlx_texture_t *tex;

typedef struct s_fvec
{
	float	x;
	float	y;
}	t_fvec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

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

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	mlx_image_t	*image_p;
	char		**map;
	t_player	*player;
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

#endif
