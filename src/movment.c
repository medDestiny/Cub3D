/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:34:06 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/14 17:17:20 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_enemy(t_astar *astar, t_sprite *e)
{
	if (!astar->path)
		return ;
	if ((int)e->pos.x == astar->path->pos.x && (int)e->pos.y == astar->path->pos.y)
		astar->path = astar->path->parent;
	if (!astar->path)
		return ;
	if ((int)e->pos.x < astar->path->pos.x)
		e->pos.x += 1 * SPEED;
	if ((int)e->pos.y < astar->path->pos.y)
		e->pos.y += 1 * SPEED;
	if ((int)e->pos.x > astar->path->pos.x)
		e->pos.x -= 1 * SPEED;
	if ((int)e->pos.y > astar->path->pos.y)
		e->pos.y -= 1 * SPEED;
}
