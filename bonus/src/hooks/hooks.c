/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:45:09 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/01 15:47:25 by anchaouk         ###   ########.fr       */
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

void	door_hooks(mlx_key_data_t keydata, t_data *data)
{
	int		distance;
	t_ivec	new_pos;
	t_ivec	player;
	t_ivec	enemy;

	distance = UNIT;
	if (keydata.action == MLX_PRESS)
	{
		player.x = (float)data->player->pos.x / UNIT;
		player.y = (float)data->player->pos.y / UNIT;
		enemy.x = (float)data->enemy->pos.x / UNIT;
		enemy.y = (float)data->enemy->pos.y / UNIT;
		new_pos.x = data->player->pos.x + data->player->dir.x * distance;
		new_pos.y = data->player->pos.y + data->player->dir.y * distance;
		if (data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '2')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '3';
		else if (data->map[player.y][player.x] != '3'
			&& data->map[enemy.y][enemy.x] != '3'
			&& data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '3')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '2';
	}
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

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game.width = width;
	data->game.height = height;
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->game.width, data->game.height);
	if (!data->image)
		ft_error(MLX_ERR, data);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data);
	free(data->zbuffer);
	data->zbuffer = (float *)ft_malloc(width * sizeof(float), data);
}

void	close_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_all(data);
	exit(0);
}

void	hooks(void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (data->image)
		mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->game.width, data->game.height);
	if (!data->image)
		ft_error(MLX_ERR, data);
	update(data);
	render(data);
	draw_map(data); // tmp
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data);
}
