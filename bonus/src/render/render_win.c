/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:49:35 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/02 18:21:22 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	display_score(t_data *data)
{
	static mlx_image_t	*score;
	char				*time;

	if (!data->game->scene[WIN].curr_frame)
		return ;
	if (score)
		return ;
	else
	{
		time = ft_itoa((int)(mlx_get_time() - data->game->time));
		score = mlx_put_string(data->mlx, time, data->game->width / 2, data->game->height / 2);
		free(time);
	}
}

void	render_win(t_data *data)
{
	//puts("YOU WON");
	render_scene(data, WIN);
	//display_score(data);
}
