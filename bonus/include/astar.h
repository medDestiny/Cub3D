/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:23:35 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:22:42 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTAR_H
# define ASTAR_H

# include "vectors.h"

/*
 * A-Star Algorithm:
 * (used for path finding between the enemy and player in the maze)
 */

typedef struct s_data	t_data;

typedef enum e_neighbour
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
}	t_neighbour;

typedef struct s_node
{
	short int		is_wall;
	short int		is_visited;
	float			g_goal;
	float			l_goal;
	t_ivec			pos;
	struct s_node	*neighbour[4];
	struct s_node	*parent;
}	t_node;

typedef struct s_astar
{
	t_node	**grid;
	t_node	*path;
	t_ivec	max;
}	t_astar;

//		Gets the path between s (start) and e (end)
t_node	*find_path(t_data *data, t_ivec s, t_ivec e);

//		Gets the size of the maze grid
t_ivec	get_max_size(char **map);

//		Allocates the nodes of the grid
t_node	**init_nodes(t_ivec max, t_data *data);

//		Initializes the nodes of the grid
void	reset_grid(t_node **grid, char **map, t_ivec max);

typedef struct s_lst
{
	t_node			*node;
	struct s_lst	*next;
}	t_lst;

//		Astar nodes list functions
void	lst_insert(t_lst **lst, t_node *node, t_data *data);
void	lst_del_one(t_lst **lst);
void	clean_list(t_lst **lst);

#endif
