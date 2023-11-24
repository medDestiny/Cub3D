/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/24 17:48:46 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*get_player_data(t_data *data)
{
	int			i;
	int			j;
	t_player	*player;

	player = (t_player *)ft_malloc(sizeof(t_player), data);
	if (!player)
		return (NULL);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
				break ;
			j++;
		}
		if (data->map[i][j] && (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W'))
			break ;
		i++;
	}
	player->pos.x = j * UNIT + UNIT / 2;
	player->pos.y = i * UNIT + UNIT / 2;
	player->angle = get_player_angle(data->map[i][j]);
	return (player);
}

void	init_data(t_data *data)
{
	//data->enemy->texture[0] = mlx_load_png("textures/bacteria1.png");
	//data->enemy->texture[1] = mlx_load_png("textures/bacteria2.png");
	//data->enemy->texture[2] = mlx_load_png("textures/bacteria3.png");
	//data->enemy->texture[3] = mlx_load_png("textures/bacteria4.png");
	//data->enemy->texture[4] = mlx_load_png("textures/bacteria5.png");

	// temp
	t = mlx_load_png("textures/backrooms.png");
	d = mlx_load_png("textures/door_exit.png");
	h = mlx_load_png("textures/hud1.png");

	//data->textures[NO] = mlx_load_png("textures/backrooms_w.png");
	//data->textures[SO] = mlx_load_png("textures/backrooms_w.png");
	//data->textures[EA] = mlx_load_png("textures/backrooms_w.png");
	//data->textures[WE] = mlx_load_png("textures/backrooms_w.png");

	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI); // temporairly
	//data->player = get_player_data(data);

	// these are for the bonus
	data->enemy = (t_sprite *)ft_malloc(sizeof(t_sprite), data);
	data->astar = (t_astar *)ft_malloc(sizeof(t_astar), data);
	data->zbuffer = (float *)ft_malloc(WIN_WID * sizeof(float), data);
	data->enemy->pos.x = 9 * UNIT + UNIT / 2;
	data->enemy->pos.y = 1 * UNIT + UNIT / 2;
	data->astar->max = get_max_size(data->map);
	data->astar->grid = init_nodes(data->astar->max, data);
	data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));

	data->game.width = WIN_WID;
	data->game.height = WIN_HEI;
	//get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
}

float	fix_angle(float angle)
{
	if (angle < 0)
		return (angle + M_PI * 2);
	else if (angle > 2 * M_PI)
		return (angle - M_PI * 2);
	return (angle);
}

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
		player.x = (int)data->player->pos.x / UNIT;
		player.y = (int)data->player->pos.y / UNIT;
		enemy.x = (int)data->player->pos.x / UNIT;
		enemy.y = (int)data->player->pos.y / UNIT;
		new_pos.x = data->player->pos.x + data->player->dir.x * distance;
		new_pos.y = data->player->pos.y + data->player->dir.y * distance;
		if (data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '2')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '3';
		else if (data->map[player.y / UNIT][player.x / UNIT] != '3'
			&& data->map[enemy.y / UNIT][enemy.x / UNIT] != '3'
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

void	draw_sprite(t_data *data, t_sprite *sp);
void	draw_hud(t_data *data);
void	move_enemy(t_astar *astar, t_sprite *e, t_player *p);

void	hooks(void *param)
{
	t_data		*data;
	static int	time; // for bonus

	data = (t_data *)param;
	move_player(data);
	if (time > 20)
	{
		data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));
		time = 0;
	}
	if (data->image_p)
		mlx_delete_image(data->mlx, data->image_p);
	data->image_p = mlx_new_image(data->mlx, data->game.width, data->game.height);
	move_enemy(data->astar, data->enemy, data->player);
	//draw_player(data->image_p, data->player);
	//draw_circle(data->image_p, data->enemy->pos, 5, 0x111111FF);
	draw_scene(data);
	//draw_sprite(data, data->enemy);
	//draw_hud(data);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
	time++;
	//printf("FPS:%.0f\n", 1.0 / data->mlx->delta_time);
}

void	resize_window(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game.width = width;
	data->game.height = height;
	mlx_delete_image(data->mlx, data->image_p);
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, data->game.width, data->game.height);
	data->image_p = mlx_new_image(data->mlx, data->game.width, data->game.height);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
	free(data->zbuffer);
	data->zbuffer = (float *)ft_malloc(width * sizeof(float), data);
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_hooks, data);
	mlx_resize_hook(data->mlx, resize_window, data);
	mlx_loop_hook(data->mlx, hooks, data);
}

void	lek(void)
{
	system("leaks cub3D");
}

t_ivec	fvec_to_ivec(t_fvec x)
{
	return ((t_ivec){(int)x.x, (int)x.y});
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(lek); // moooohsiine

	parser(av, ac, &data);
	init_data(&data);
	//draw_map(data.image, data.map);
	//draw_player(data.image_p, data.player);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	// clean_all(&data);
}
