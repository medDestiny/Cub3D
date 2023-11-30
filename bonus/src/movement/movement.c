/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 20:34:06 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/30 15:09:56 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	move_enemy(t_astar *astar, t_sprite *e, float speed)
{
	float	multiplier;


	if (!astar->path)
		return ;
	if (abs((int)e->pos.x - astar->path->pos.x) <= UNIT / 4
		&& abs((int)e->pos.y - astar->path->pos.y) <= UNIT / 4)
		astar->path = astar->path->parent;
	if (!astar->path)
		return ;
	multiplier = 0.7;
	if ((int)e->pos.x < astar->path->pos.x)
		e->pos.x += multiplier * speed;
	if ((int)e->pos.y < astar->path->pos.y)
		e->pos.y += multiplier * speed;
	if ((int)e->pos.x > astar->path->pos.x)
		e->pos.x -= multiplier * speed;
	if ((int)e->pos.y > astar->path->pos.y)
		e->pos.y -= multiplier * speed;
}

void	initiate_move(t_player *p, float speed, char **map, float angle)
{
	t_fvec	pos;
	t_fvec	dir;

	get_dir_vector(&dir.x, &dir.y, angle);
	pos.x = dir.x * speed;
	pos.y = dir.y * speed;
	if (is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT])
		&& is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		return ;
	if (!is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT]))
		p->pos.x += pos.x;
	if (!is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		p->pos.y += pos.y;
}

void	move_player(t_data *data)
{
	float	speed;

	speed = data->player->speed * data->mlx->delta_time;
	if (data->player->move.front == 1)
		initiate_move(data->player, speed, data->map, fix_angle(data->player->angle));
	if (data->player->move.back == 1)
		initiate_move(data->player, speed, data->map, \
		fix_angle(data->player->angle + M_PI));
	if (data->player->move.left == 1)
		initiate_move(data->player, speed, data->map, \
		fix_angle(data->player->angle - M_PI / 2));
	if (data->player->move.right == 1)
		initiate_move(data->player, speed, data->map, \
		fix_angle(data->player->angle + M_PI / 2));
}
