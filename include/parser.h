/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:55:22 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/16 12:00:10 by mmisskin         ###   ########.fr       */
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

typedef struct s_data	t_data;

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

void	check_extension(char *str);

#endif
