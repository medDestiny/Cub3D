/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:45:09 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/29 17:28:08 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	strafe_hooks(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE) 
		data->player->move.front = 1;
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE) 
		data->player->move.front = 0;
	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
		data->player->move.back = 1;
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		data->player->move.back = 0;
	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
		data->player->move.left = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		data->player->move.left = 0;
	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
		data->player->move.right = 1;
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		data->player->move.right = 0;
}

void	cursor_rotate(double xpos, double ypos, void *param)
{
	t_data		*data;
	int32_t		x;
	int32_t		y;

	data = (t_data *)param;
	if (data->game->state != PLAYING)
		return ;
	(void)ypos;
	y = 0;
	x = (int)xpos;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	mlx_set_mouse_pos(data->mlx, data->game->width / 2, data->game->height / 2);
	if (x >= (int)data->game->width / 2 && x < (int)data->game->width)
		data->player->angle += 2.9 * M_PI / 180;
	else if (x < (int)data->game->width / 2 && x >= 0)
		data->player->angle -= 2.9 * M_PI / 180;
	data->player->angle = fix_angle(data->player->angle);
	get_dir_vector(&data->player->dir.x, &data->player->dir.y,
		data->player->angle);
}

void	rotate_hooks(mlx_key_data_t keydata, t_data *data)
{
	float	angle;

	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		data->player->angle += 5 * M_PI / 180;
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		data->player->angle -= 5 * M_PI / 180;
	data->player->angle = fix_angle(data->player->angle);
	angle = data->player->angle;
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, angle);
}

void	key_hooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		clean_all(data);
		exit(0);
	}
	check_game_keys(keydata, data);
	if (keydata.key == MLX_KEY_W
		|| keydata.key == MLX_KEY_A
		|| keydata.key == MLX_KEY_S
		|| keydata.key == MLX_KEY_D)
		strafe_hooks(keydata, data);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		rotate_hooks(keydata, data);
	if (keydata.key == MLX_KEY_E)
		door_hooks(keydata, data);
}

void	hooks(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->game->width,
			data->game->height);
	if (!data->image)
		ft_error(MLX_ERR, data, clean_all);
	update(data);
	render(data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data, clean_all);
}
