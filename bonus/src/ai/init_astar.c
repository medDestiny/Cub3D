/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_astar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:16:47 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/07 18:15:33 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_ivec	get_max_size(char **map)
{
	int		len;
	t_ivec	max;

	max.x = 0;
	max.y = 0;
	while (map[max.y])
	{
		len = ft_strlen(map[max.y]);
		if (len > max.x)
			max.x = len;
		max.y++;
	}
	return (max);
}

void	set_node_neighbours(t_node **grid, int x, int y, t_ivec max)
{
	if (y > 0)
		grid[y][x].neighbor[UP] = &grid[y - 1][x];
	else
		grid[y][x].neighbor[UP] = NULL;
	if (y < max.y - 1)
		grid[y][x].neighbor[DOWN] = &grid[y + 1][x];
	else
		grid[y][x].neighbor[DOWN] = NULL;
	if (x > 0)
		grid[y][x].neighbor[LEFT] = &grid[y][x - 1];
	else
		grid[y][x].neighbor[LEFT] = NULL;
	if (x < max.x - 1)
		grid[y][x].neighbor[RIGHT] = &grid[y][x + 1];
	else
		grid[y][x].neighbor[RIGHT] = NULL;
}

void	fill_node_data(t_node **grid, char **map, t_ivec pos, t_ivec max)
{
	if ((int)ft_strlen(map[pos.y]) <= pos.x)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == '2')
		grid[pos.y][pos.x].is_wall = 1;
	else
		grid[pos.y][pos.x].is_wall = 0;
	grid[pos.y][pos.x].is_visited = 0;
	grid[pos.y][pos.x].g_goal = -1;
	grid[pos.y][pos.x].l_goal = -1;
	grid[pos.y][pos.x].pos.x = pos.x * UNIT + UNIT / 2;
	grid[pos.y][pos.x].pos.y = pos.y * UNIT + UNIT / 2;
	set_node_neighbours(grid, pos.x, pos.y, max);
	grid[pos.y][pos.x].parent = NULL;
}

t_node	**init_nodes(t_ivec max, t_data *data)
{
	int		k;
	t_node	**grid;

	grid = (t_node **)ft_malloc(max.y * sizeof(t_node *), data, clean_all);
	k = 0;
	while (k < max.y)
	{
		grid[k] = (t_node *)ft_malloc(max.x * sizeof(t_node), data, clean_all);
		k++;
	}
	return (grid);
}

void	reset_grid(t_node **grid, char **map, t_ivec max)
{
	t_ivec	pos;

	pos.y = 0;
	while (pos.y < max.y)
	{
		pos.x = 0;
		while (pos.x < max.x)
		{
			fill_node_data(grid, map, pos, max);
			pos.x++;
		}
		pos.y++;
	}
}
