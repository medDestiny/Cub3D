/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:56:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/06 16:08:28 by mmisskin         ###   ########.fr       */
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
# define UNIT 50
# define SPEED UNIT / 10 * 0.5
# define FOV 60
# define DOF 1000 * UNIT

// COORDINATES

# define NO 0
# define SO 1
# define WE 2
# define EA 3

// ERROR CODES

# define OPEN_ERR -1
# define EXT_ERR -2
# define MAP_EMPTY -3
# define DUP_CORD -4
# define INVA_CORD -5
# define TEX_LOAD_ERR -6
# define MAP_EXIST -7
# define CORD_MIS -8
# define FLOOR_INV -9
# define CIELING_INV -10
# define INV_INPUT -11
# define DUP_COLOR -12
# define COLOR_RANGE -13
# define MAP_INV -14
# define MALLOC_ERR -16

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
	mlx_image_t		*image;
	mlx_image_t		*image_p;
	mlx_t			*mlx;
	t_player		*player;
	mlx_texture_t	*textures[4];
	uint32_t		floor_color;
	uint32_t		cieling_color;
	int				floor_flag;
	int				cieling_flag;
	char			**map;
	int				player_flag;
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

void	get_dir_vector(float *x, float *y, float angle);

//		Drawing functions
void	draw_player(mlx_image_t *image, t_player *player);
void	draw_circle(mlx_image_t *image, t_fvec c, int rad, int color);
void	draw_map(mlx_image_t *img, char **map);
void	draw_square(mlx_image_t *image, t_ivec p, int size, int color);
void	draw_line(mlx_image_t *image, t_fvec p1, t_fvec p2, int color);
void	draw_scene(t_data *data);

// parsing functions

void	parser(char **av, int ac, t_data *data);
int		read_map_elements(int map_fd, t_data **data, char *map_path);
int		open_file(char *str, t_data *data);
void	ft_error(int err_code, t_data *data);
void	fl_cl_check(int map_fd, t_data *data);
void	load_cieling(t_data *data, char **split);
void	load_floor(t_data *data, char **split);
int		ft_arraylen(char **arr);
char	**get_map(int map_fd, char *map_path, t_data *data);
char	*skip_map_elements(int map_fd);
void	check_map_spaces(char **map, t_data *data);
void	parse_map(char **map, t_data *data);
void	parse_map_m(char *map_str, t_data *data);
void	parse_map_fl(char *map_str, t_data *data);
void	init_map(char **map, t_data *data);
//		Ray Casting function
void	cast_ray(t_data *data, t_ray *ray, int pos);

//		Checking for walls
int		is_wall(char pos);

#endif
