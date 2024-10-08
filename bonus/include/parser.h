/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:55:22 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/08 01:07:52 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// COORDINATES

# define NO 0
# define SO 1
# define WE 2
# define EA 3

// ERROR CODES

typedef enum e_error
{
	OPEN_ERR = -1,
	EXT_ERR = -2,
	MAP_EMPTY = -3,
	DUP_CORD = -4,
	INVA_CORD = -5,
	TEX_LOAD_ERR = -6,
	MAP_EXIST = -7,
	CORD_MIS = -8,
	FLOOR_INV = -9,
	CEILING_INV = -10,
	INV_INPUT = -11,
	DUP_COLOR = -12,
	COLOR_RANGE = -13,
	MAP_INV = -14,
	MALLOC_ERR = -16,
	PLAYER_DUP = -17,
	ARG_ERR = -18,
	MLX_ERR = -19,
	DOOR_ERR = -20,
	DOOR_INV = -21,
	ENEMY_DUP = -22,
	PLAYER_MIS = -23,
	ENEMY_MIS = -24,
	GOAL_MIS = -25,
	GOAL_DUP = -26,
	ENEMY_TEX_ERR = -27,
	FLOOR_MIS = -28,
	CEIL_MIS = -29
}	t_error;

typedef struct s_data	t_data;

typedef struct s_minimap
{
	t_ivec	p;
	t_ivec	s;
	t_ivec	e;
	t_fvec	ratio;
	t_fvec	center;
	float	left;
	float	right;
	float	y_rat;
	size_t	unit;
	size_t	i;
	size_t	d;
}	t_minimap;

//			parsing functions
void		parser(char **av, int ac, t_data *data);
void		get_parsed_map(int map_fd, char *map_path, t_data *data);
void		parse_map(t_data *data);
void		parse_map_fl(char *map_str, t_data *data);
void		init_map(t_data *data);
char		*space_iter(char *str);
void		init_map_elements(int map_fd, t_data *data, char *map_path);
char		*newline_iter(int map_fd, char *str_read);
int			file_empty(int fd);

//			tools functions
size_t		get_map_size(int fd);
size_t		arr_len(char **arr);
int			open_file(char *str, t_data *data);
void		free_content(char *str, char **splitted_str, char *trimmed);
void		ft_error(int err_code, t_data *data, void (clean)(t_data *));

//			checker functions
int			check_lines(char **map, size_t i, size_t pos, t_data *data);
void		check_map_spaces(t_data *data);
void		check_map_leftovers(int fd, t_data *data);
void		check_door(t_data *data, size_t i, size_t pos);
int			check_textures(mlx_texture_t **textures);
void		check_map_spaces(t_data *data);
void		check_entities(t_data *data, char *map_line, int y);
int			check_floor_player(char c);
void		check_colors(t_data *data);

//			loading functions
int			comma_count(char *colors);
void		load_cieling(t_data *data, char **split);
void		load_floor(t_data *data, char **split);
int			load_texture(t_data *data, char **str, int index, char *str_read);

//			floor and cieling functions
int			comma_count(char *colors);
uint32_t	merge_rgba(char **colors, t_data *data);
int			parse_color(char **colors);

//			init entities tools
float		get_player_angle(char p);
void		init_enemy(char *line, int x, int y, t_data *data);
void		init_player(char *line, int x, int y, t_data *data);
void		fill_goal(t_data *data, int x, int y, char *line);
void		fill_sprites(t_data *data, int x, int y, char *line);

#endif
