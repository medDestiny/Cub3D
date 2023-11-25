/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:05:03 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:22:38 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	get_distance(t_ivec a, t_ivec b)
{
	return (sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)));
}

void	check_neighbour_nodes(t_node *current, t_lst **to_test, t_ivec e_pos,
		t_data *data)
{
	t_node	*neighbour;
	float	new_goal;
	int		i;

	i = -1;
	while (++i < 4)
	{
		neighbour = current->neighbour[i];
		if (!neighbour)
			continue ;
		new_goal = current->l_goal + get_distance(current->pos, neighbour->pos);
		if (neighbour->l_goal == -1 || new_goal < neighbour->l_goal)
		{
			neighbour->parent = current;
			neighbour->l_goal = new_goal;
			neighbour->g_goal = new_goal + get_distance(neighbour->pos, e_pos);
		}
		if (neighbour && !neighbour->is_visited && !neighbour->is_wall)
			lst_insert(to_test, neighbour, data);
	}
}

t_node	*find_path(t_data *data, t_ivec s, t_ivec e)
{
	t_node	*start;
	t_node	*end;
	t_node	*current;
	t_lst	*to_test;

	to_test = NULL;
	reset_grid(data->astar->grid, data->map, data->astar->max);
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
