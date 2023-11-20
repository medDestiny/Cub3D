/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/20 10:55:02 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


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
	data->enemy->texture[0] = mlx_load_png("textures/bacteria1.png");
	data->enemy->texture[1] = mlx_load_png("textures/bacteria2.png");
	data->enemy->texture[2] = mlx_load_png("textures/bacteria3.png");
	data->enemy->texture[3] = mlx_load_png("textures/bacteria4.png");
	data->enemy->texture[4] = mlx_load_png("textures/bacteria5.png");
	t = mlx_load_png("textures/backrooms.png");
	d = mlx_load_png("textures/door.png");
	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->map = read_map(path);
	data->player = get_player_data(data->map);
	data->player_flag = 0;
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
}

void	move_front(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT]) && is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		return ;
	if (!is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT]))
		p->pos.x += pos.x;
	if (!is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		p->pos.y += pos.y;
}

void	move_back(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT]) && is_wall(map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT]))
		return ;
	if (!is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT]))
		p->pos.x -= pos.x;
	if (!is_wall(map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT]))
		p->pos.y -= pos.y;
}

void	move_right(t_player *p, char **map)
{
	t_fvec	pos;
	t_fvec	strafe;

	get_dir_vector(&strafe.x, &strafe.y, p->angle + M_PI / 2);
	pos.x = strafe.x * SPEED;
	pos.y = strafe.y * SPEED;
	if (is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT]) && is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		return ;
	if (!is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT]))
		p->pos.x += pos.x;
	if (!is_wall(map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT]))
		p->pos.y += pos.y;
}

void	move_left(t_player *p, char **map)
{
	t_fvec	pos;
	t_fvec	strafe;

	get_dir_vector(&strafe.x, &strafe.y, p->angle + M_PI / 2);
	pos.x = strafe.x * SPEED;
	pos.y = strafe.y * SPEED;
	if (is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT]) && is_wall(map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT]))
		return ;
	if (!is_wall(map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT]))
		p->pos.x -= pos.x;
	if (!is_wall(map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT]))
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

void	door_hooks(mlx_key_data_t keydata, t_data *data)
{
	int		distance;
	t_ivec	new_pos;

	distance = UNIT;
	if (keydata.action == MLX_PRESS)
	{
		new_pos.x = data->player->pos.x + data->player->dir.x * distance;
		new_pos.y = data->player->pos.y + data->player->dir.y * distance;
		if (data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '2')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '3';
		else if (data->map[(int)data->player->pos.y / UNIT][(int)data->player->pos.x / UNIT] != '3' && data->map[new_pos.y / UNIT][new_pos.x / UNIT] == '3')
			data->map[new_pos.y / UNIT][new_pos.x / UNIT] = '2';
	}
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
	if (keydata.key == MLX_KEY_E)
		door_hooks(keydata, data);
}

void	draw_sprite(t_data *data, t_sprite *sp);
void	move_enemy(t_astar *astar, t_sprite *e, t_player *p);

void	hooks(void *param)
{
	t_data	*data;
	static int time;

	data = (t_data *)param;
	if (data->player->move.front == 1)
		move_front(data->player, data->map);
	if (data->player->move.back == 1)
		move_back(data->player, data->map);
	if (data->player->move.left == 1)
		move_left(data->player, data->map);
	if (data->player->move.right == 1)
		move_right(data->player, data->map);
	if (time > 20)
	{
		data->astar->path = find_path(data->astar, data->map, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));
		time = 0;
	}
	if (data->image_p)
		mlx_delete_image(data->mlx, data->image_p);
	data->image_p = mlx_new_image(data->mlx, data->game.width, data->game.height);
	move_enemy(data->astar, data->enemy, data->player);
	//draw_player(data->image_p, data->player);
	//draw_circle(data->image_p, data->enemy->pos, 5, 0x111111FF);
	draw_scene(data);
	draw_sprite(data, data->enemy);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
	time++;
	//printf("FPS:%.0f\n", 1.0 / data->mlx->delta_time);
}

void	resize_window(int32_t width, int32_t height, void* param)
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
	data->zbuffer = (float *)malloc(width * sizeof(float));
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

	(void)ac;
	//parser(av, ac, &data);
	if (ac != 2)
		return (1);
	data.enemy = (t_sprite *)malloc(sizeof(t_sprite));
	data.astar = (t_astar *)malloc(sizeof(t_astar));
	data.zbuffer = (float *)malloc(WIN_WID * sizeof(float));
	data.enemy->pos.x = 2 * UNIT + UNIT / 2;
	data.enemy->pos.y = 12 * UNIT + UNIT / 2;
	data.game.width = WIN_WID;
	data.game.height = WIN_HEI;
	atexit(lek);
	init_data(&data, av[1]);
	data.astar->max = get_max_size(data.map);
	data.astar->grid = init_nodes(data.astar->max);
	data.astar->path = find_path(data.astar, data.map, fvec_to_ivec(data.player->pos), fvec_to_ivec(data.enemy->pos));
	//draw_map(data.image, data.map);
	//draw_player(data.image_p, data.player);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	clean_all(&data);
}
