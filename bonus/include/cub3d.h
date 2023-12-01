/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:56:26 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 10:55:20 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../../MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"
# include "astar.h"
# include "vectors.h"
# include "parser.h"
# include "sprite.h"
# include "player.h"
# include "scene.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define WIN_WID 1280
# define WIN_HEI 960
# define UNIT 3000
# define FOV 60
# define DOF 100000000000

# define HORI_WALL 1
# define VERT_WALL 0

# define SANITY 1000
# define SEARCH_DIST 50

typedef enum e_state
{
	PLAYING = -1,
	MENU = 0,
	PAUSED = 1,
	DEATH = 2,
	INSANITY = 3,
	WIN = 4
}	t_state;

typedef struct s_game
{
	t_state			state;
	t_scene			scene[5];
	double			time;
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
	t_sprite		*enemy;
	t_sprite		*goal;
	t_sp_list		*sprites;
	t_player		*player;
	t_astar			*astar;
	t_game			*game;
	char			**map;
	char			**saved_map;
	float			*zbuffer;
	mlx_texture_t	*textures[4];
	mlx_texture_t	*door;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
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

mlx_texture_t *h;
mlx_texture_t *spr[5];

//			Drawing functions
void		draw_player(mlx_image_t *image, t_player *player);
void		draw_circle(mlx_image_t *image, t_fvec c, int rad, int color);
void		draw_map(mlx_image_t *img, char **map);
void		draw_square(mlx_image_t *image, t_ivec p, int size, int color);
void		draw_line(mlx_image_t *image, t_fvec p1, t_fvec p2, int color);
void		draw_scene(t_data *data);
void		draw_ceiling(t_data *data, int x, int end, uint32_t color);
void		draw_floor(t_data *data, int x, int start, uint32_t color);
void		draw_stripe(t_data *data, t_ray *ray, int pos, int side);

//			Input registration
void		strafe_hooks(mlx_key_data_t keydata, t_data *data);
void		rotate_hooks(mlx_key_data_t keydata, t_data *data);
void		check_game_keys(mlx_key_data_t keydata, t_data *data);
void		key_hooks(mlx_key_data_t keydata, void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		close_hook(void *param);
void		door_hooks(mlx_key_data_t keydata, t_data *data);
void		cursor_rotate(double xpos, double ypos, void *param);
void		hooks(void *param);

//			Keeps game data up to date (runs each frame)
void		update(t_data *data);

//			Renders the game
void		render(t_data *data);

//			Rendring functions
void		render_game(t_data *data);
void		render_win(t_data *data);
void		render_death(t_data *data);
void		render_insanity(t_data *data);
void		render_menu(t_data *data);
void		render_pause(t_data *data);

//			Moves the enemy towards the player
void		move_enemy(t_astar *astar, t_sprite *e, float speed);

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

//			Darkens a given color by a factor [0, 1]
uint32_t	darken_color(uint32_t color, float factor);

//			Resets game data
void		reset_game(t_data *data);
void		reset_player_mvm(t_player *p);
void		disable_game_scenes(t_data *data);

//			Memory management
void		*ft_malloc(size_t size, t_data *data, void (clean)(t_data *));
void		clean_all(t_data *data);
void		clean_parsing(t_data *data);
void		clean_vec(char **vec);
void		clean_scenes(t_data *data);
void		clean_sprite(t_sprite *sp);
void		clean_sprite_list(t_sp_list *sprites);

#endif
