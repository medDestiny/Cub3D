/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:55:22 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/24 11:25:57 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>

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
# define PLAYER_DUP -17

typedef struct s_data	t_data;

// parsing functions

void	parser(char **av, int ac, t_data *data);
int		open_file(char *str, t_data *data);
void	ft_error(int err_code, t_data *data);
int		ft_arraylen(char **arr);
char	**get_parsed_map(int map_fd, char *map_path, t_data *data);
char	*skip_map_elements(int map_fd, t_data *data);
void	parse_map(char **map, t_data *data);
void	parse_map_fl(char *map_str, t_data *data);
void	init_map(char **map, t_data *data);
float	get_player_angle(char p);
char	*space_iter(char *str);
void	check_extension(char *str);
void		init_map_elements(int map_fd, t_data **data, char *map_path);
size_t	arr_len(char **arr);
void	free_arr(char **arr);
char	*newline_iter(int map_fd, char *str_read);
void	free_content(char *str, char **splitted_str, char *trimmed);
size_t	get_map_size(int fd);
int		check_wall_player(char c);
void	check_dup_player(char **map, t_data *data);
void	check_map_spaces(char **map, t_data *data);
void	check_map_leftovers(int fd, t_data *data);
size_t	file_len(int fd);
//loading functions
void	load_cieling(t_data *data, char **split);
void	load_floor(t_data *data, char **split);
int		load_texture(t_data *data, char **str, int index, char *str_read);
//floor and cieling functions
int			comma_count(char *colors);
uint32_t	merge_rgba(char **colors, t_data *data);
int			parse_color(char **colors);

#endif
