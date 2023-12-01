/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 22:43:02 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/27 23:36:09 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

//static void	check_mouse

void	cursor_rotate(double xpos, double ypos, void* param)
{
	t_data	*data;
	int32_t	x;
	int32_t	y;
	static int	key_bool;

	data = (t_data *)param;
	x = (int)xpos;
	y = 0;
	(void)ypos;
	if (mlx_is_mouse_down(data->mlx, 1))
	{
		if (!key_bool)
		{
			key_bool = 1;
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		}
		else if (key_bool)
		{
			mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
			key_bool = 0;
		}
	}
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (key_bool == 0)
		mlx_set_mouse_pos(data->mlx, data->game.width / 2, data->game.height / 2);
	if ( x >= (int)data->game.width / 2 && x < (int)data->game.width)
		data->player->angle += 2.9 * M_PI / 180;
	else if (x < (int)data->game.width / 2 && x >= 0)
		data->player->angle -= 2.9 * M_PI / 180;
	data->player->angle = fix_angle(data->player->angle);
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
}
