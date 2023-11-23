/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:05:03 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/23 17:00:46 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		grid[y][x].neighbour[UP] = &grid[y - 1][x];
	else
		grid[y][x].neighbour[UP] = NULL;
	if (y < max.y - 1)
		grid[y][x].neighbour[DOWN] = &grid[y + 1][x];
	else
		grid[y][x].neighbour[DOWN] = NULL;
	if (x > 0)
		grid[y][x].neighbour[LEFT] = &grid[y][x - 1];
	else
		grid[y][x].neighbour[LEFT] = NULL;
	if (x < max.x - 1)
		grid[y][x].neighbour[RIGHT] = &grid[y][x + 1];
	else
		grid[y][x].neighbour[RIGHT] = NULL;
}

void	fill_node_data(t_node **grid, char **map, t_ivec pos, t_ivec max)
{
	if ((int)ft_strlen(map[pos.y]) - 1 <= pos.x)
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

t_node	**init_nodes(t_ivec max)
{
	int		k;
	t_node	**grid;

	grid = (t_node **)malloc(max.y * sizeof(t_node *));
	if (!grid)
	{
		// free and exit
	}
	k = 0;
	while (k < max.y)
	{
		grid[k] = (t_node *)malloc(max.x * sizeof(t_node));
		if (!grid[k])
		{
			// free and exit
		}
		k++;
	}
	return (grid);
}

float	get_distance(t_ivec a, t_ivec b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

void	insert(t_lst **lst, t_node *node, t_lst *new)
{
	t_lst	*hold;
	t_lst	*tmp;

	tmp = *lst;
	hold = NULL;
	while (tmp && tmp->node && tmp->node->g_goal < node->g_goal)
	{
		hold = tmp;
		tmp = tmp->next;
	}
	new->node = node;
	new->next = tmp;
	if (hold)
		hold->next = new;
	else
		*lst = new;
}

void	lst_insert(t_lst **lst, t_node *node)
{
	t_lst	*tmp;
	t_lst	*new;

	tmp = *lst;
	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
		return ;
	if (!tmp)
	{
		*lst = new;
		tmp = *lst;
	}
	else
		return (insert(lst, node, new));
	tmp->node = node;
	tmp->next = NULL;
}

void	lst_del_one(t_lst **lst)
{
	t_lst	*next;

	if (!lst || !*lst)
		return ;
	next = (*lst)->next;
	free(*lst);
	*lst = next;
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

void	check_neighbour_nodes(t_node *current, t_lst **to_test, t_ivec e_pos)
{
	t_node	*neighbour;
	float	new_goal;
	int		i;

	i = 0;
	while (i < 4)
	{
		neighbour = current->neighbour[i];
		new_goal = current->l_goal + get_distance(current->pos, neighbour->pos);
		if (neighbour->l_goal == -1 || new_goal < neighbour->l_goal)
		{
			neighbour->parent = current;
			neighbour->l_goal = new_goal;
			neighbour->g_goal = new_goal + get_distance(neighbour->pos, e_pos);
		}
		if (neighbour && !neighbour->is_visited && !neighbour->is_wall)
			lst_insert(to_test, neighbour);
		i++;
	}
}

t_node	*find_path(t_astar *astar, char **map, t_ivec s, t_ivec e)
{
	t_node	*start;
	t_node	*end;
	t_node	*current;
	t_lst	*to_test;

	to_test = NULL;
	reset_grid(astar->grid, map, astar->max);
	start = &astar->grid[(int)s.y / UNIT][(int)s.x / UNIT];
	start->l_goal = 0;
	start->g_goal = get_distance(s, e);
	end = &astar->grid[(int)e.y / UNIT][(int)e.x / UNIT];
	lst_insert(&to_test, start);
	while (to_test && current != end)
	{
		while (to_test && to_test->node->is_visited == 1)
			lst_del_one(&to_test);
		if (!to_test)
			break ;
		current = to_test->node;
		current->is_visited = 1;
		check_neighbour_nodes(current, &to_test, end->pos);
	}
	if (current != end)
		return (NULL);
	return (current);
}
