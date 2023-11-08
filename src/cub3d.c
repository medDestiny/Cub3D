/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/08 18:10:52 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t *tex = NULL;

void	clean_vec(char **vec)
{
	int	i;

	i = 0;
	while (vec && vec[i])
	{
		free(vec[i]);
		i++;
	}
	free(vec);
}

float	get_player_angle(char p)
{
	float	angle;

	if (p == 'N')
		angle = 3 * M_PI / 2;
	else if (p == 'S')
		angle = M_PI / 2;
	else if (p == 'W')
		angle = M_PI;
	else
		angle = 0;
	return (angle);
}

void	get_dir_vector(float *x, float *y, float angle)
{
	*x = cos(angle);
	*y = sin(angle);
}

t_player	*get_player_data(char **map)
{
	int			i;
	int			j;
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
				break ;
			j++;
		}
		if (map[i][j] && (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W'))
			break ;
		i++;
	}
	player->pos.x = j * UNIT + UNIT / 2;
	player->pos.y = i * UNIT + UNIT / 2;
	player->angle = get_player_angle(map[i][j]);
	return (player);
}

void	init_data(t_data *data, char *path)
{
	(void)path;
	tex = mlx_load_png("textures/zelij.png");
	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->map = read_map(path);
	data->player = get_player_data(data->map);
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
}

void	move_front(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] == '1' && map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] == '1')
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] != '1')
		p->pos.x += pos.x;
	if (map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] != '1')
		p->pos.y += pos.y;
}

void	move_back(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] == '1' && map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] == '1')
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] != '1')
		p->pos.x -= pos.x;
	if (map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] != '1')
		p->pos.y -= pos.y;
}

void	move_right(t_player *p, char **map)
{
	t_fvec	pos;
	t_fvec	strafe;

	get_dir_vector(&strafe.x, &strafe.y, p->angle + M_PI / 2);
	pos.x = strafe.x * SPEED;
	pos.y = strafe.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] == '1' && map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] == '1')
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] != '1')
		p->pos.x += pos.x;
	if (map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] != '1')
		p->pos.y += pos.y;
}

void	move_left(t_player *p, char **map)
{
	t_fvec	pos;
	t_fvec	strafe;

	get_dir_vector(&strafe.x, &strafe.y, p->angle + M_PI / 2);
	pos.x = strafe.x * SPEED;
	pos.y = strafe.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] == '1' && map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] == '1')
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] != '1')
		p->pos.x -= pos.x;
	if (map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] != '1')
		p->pos.y -= pos.y;
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
	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
		data->player->angle += 5 * M_PI / 180;
	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
		data->player->angle -= 5 * M_PI / 180;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	if (data->player->angle > 2 * M_PI)
		data->player->angle -= 2 * M_PI;
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
}

void	clean_all(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_delete_image(data->mlx, data->image_p);
	mlx_close_window(data->mlx);
	clean_vec(data->map);
	free(data->player);
	mlx_terminate(data->mlx);
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
	if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
		strafe_hooks(keydata, data);
	if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		rotate_hooks(keydata, data);
}

void	hooks(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->player->move.front == 1)
		move_front(data->player, data->map);
	if (data->player->move.back == 1)
		move_back(data->player, data->map);
	if (data->player->move.left == 1)
		move_left(data->player, data->map);
	if (data->player->move.right == 1)
		move_right(data->player, data->map);
	if (data->image_p)
		mlx_delete_image(data->mlx, data->image_p);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	//draw_player(data->image_p, data->player);
	draw_scene(data);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
	//printf("FPS:%.0f\n", 1.0 / data->mlx->delta_time);
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_hooks, data);
	mlx_loop_hook(data->mlx, hooks, data);
}

void	lek(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	parser(av, ac, &data);
	init_data(&data, av[1]);
	// atexit(lek);
	//draw_map(data.image, data.map);
	//draw_player(data.image_p, data.player);
	// setup_hooks(&data);
	// mlx_loop(data.mlx);
	clean_all(&data);
}
