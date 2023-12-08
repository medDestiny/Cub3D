/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:05:03 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/07 21:32:22 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	get_distance(t_ivec a, t_ivec b)
{
	t_ivec	diff;

	diff.x = abs(a.x - b.x);
	diff.y = abs(a.y - b.y);
	return (sqrt(diff.x * diff.x + diff.y * diff.y));
}

void	check_neighbour_nodes(t_node *current, t_lst **to_test, t_ivec e_pos,
		t_data *data)
{
	t_node	*neighbor;
	float	new_goal;
	int		i;

	i = -1;
	while (++i < 4)
	{
		neighbor = current->neighbor[i];
		if (!neighbor)
			continue ;
		new_goal = UNIT;
		if (neighbor->l_goal == -1)
		{
			neighbor->parent = current;
			neighbor->l_goal = new_goal;
			neighbor->g_goal = new_goal + get_distance(neighbor->pos, e_pos);
		}
		if (neighbor && !neighbor->is_visited && !neighbor->is_wall)
			lst_insert(to_test, neighbor, data);
	}
}

int	init_and_check_distance(t_data *data, float dist, t_lst **lst, t_node **cur)
{
	*lst = NULL;
	*cur = NULL;
	if (dist / UNIT <= SEARCH_DIST)
	{
		reset_grid(data->astar->grid, data->map, data->astar->max);
		return (1);
	}
	return (0);
}

t_node	*find_path(t_data *data, t_ivec s, t_ivec e)
{
	t_node	*start;
	t_node	*end;
	t_node	*current;
	t_lst	*to_test;

	if (!init_and_check_distance(data, get_distance(s, e), &to_test, &current))
		return (NULL);
	start = &data->astar->grid[(int)s.y / UNIT][(int)s.x / UNIT];
	start->l_goal = 0;
	start->g_goal = get_distance(s, e);
	end = &data->astar->grid[(int)e.y / UNIT][(int)e.x / UNIT];
	lst_insert(&to_test, start, data);
	while (to_test && current != end)
	{
		while (to_test && to_test->node->is_visited == 1)
			lst_del_one(&to_test);
		if (!to_test)
			break ;
		current = to_test->node;
		current->is_visited = 1;
		check_neighbour_nodes(current, &to_test, end->pos, data);
	}
	if (current != end)
		return (clean_list(&to_test), NULL);
	return (clean_list(&to_test), current);
}
