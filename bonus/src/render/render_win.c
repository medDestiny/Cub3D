/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:35 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/02 21:35:13 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	display_score(t_data *data)
{
	char				*time;

	if (data->game->score)
		mlx_delete_image(data->mlx, data->game->score);
	time = ft_itoa(data->player->score);
	data->game->score = mlx_put_string(data->mlx, time, data->game->width / 2, data->game->height / 2);
	free(time);
}

void	render_win(t_data *data)
{
	//puts("YOU WON");

	if (data->player->state == ALIVE)
	{
		data->player->score = (int)mlx_get_time() - (int)data->game->time;;
		printf("%.d\n", (int)mlx_get_time());
		printf("%.d\n", (int)data->game->time);
		data->player->state = WON;
	}
	render_scene(data, WIN);
	if (data->player->state == WON && data->game->scene[WIN].curr_frame == NULL)
		display_score(data);
}
