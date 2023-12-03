/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:49:30 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 20:54:40 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	check_win(t_data *data)
{
	if (fabs(data->player->pos.x - data->goal->pos.x) < UNIT / 2
		&& fabs(data->player->pos.y - data->goal->pos.y) < UNIT / 2)
		return (1);
	return (0);
}

int	check_death(t_data *data)
{
	if ((int)(data->player->pos.x / UNIT) == (int)(data->enemy->pos.x / UNIT)
		&& (int)(data->player->pos.y / UNIT) == \
		(int)(data->enemy->pos.y / UNIT))
		return (1);
	return (0);
}

void	check_for_entities(t_data *data)
{
	t_sp_list	*s;

	if (check_win(data))
		data->game->state = WIN;
	else if (check_death(data))
		data->game->state = DEATH;
	else if (data->player->sanity == 0)
		data->game->state = INSANITY;
	if (data->game->state != PLAYING)
		return ;
	s = data->sprites;
	while (s)
	{
		if (s->sp->state == ACTIVE
			&& fabs(data->player->pos.x - s->sp->pos.x) < UNIT / 2
			&& fabs(data->player->pos.y - s->sp->pos.y) < UNIT / 2
			&& data->player->sanity < SANITY)
		{
			data->player->sanity += min(SANITY - data->player->sanity, 400);
			s->sp->state = INACTIVE;
		}
		s = s->next;
	}
}
