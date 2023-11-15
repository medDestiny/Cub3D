/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:34:06 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/15 17:11:18 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	kill_player(t_sprite *e, t_player *p)
{
	if (e->pos.x < p->pos.x)
		e->pos.x += 1 * SPEED;
	if (e->pos.y < p->pos.y)
		e->pos.y += 1 * SPEED;
	if (e->pos.x > p->pos.x)
		e->pos.x -= 1 * SPEED;
	if (e->pos.y > p->pos.y)
		e->pos.y -= 1 * SPEED;
}

void	move_enemy(t_astar *astar, t_sprite *e, t_player *p)
{
	if ((int)e->pos.x / UNIT == (int)p->pos.x / UNIT && (int)e->pos.y / UNIT == (int)p->pos.y / UNIT)
		kill_player(e, p);
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
	(void)p;
}
