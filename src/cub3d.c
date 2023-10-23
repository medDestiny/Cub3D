/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 22:12:32 by mmisskin         ###   ########.fr       */
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
	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	data->map = read_map(path);
	data->player = get_player_data(data->map);
	get_dir_vector(&data->player->dir.x, &data->player->dir.y, data->player->angle);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
}

void	draw_line(mlx_image_t *image, t_fvec p1, t_fvec p2, int color)
{
	int		i;
	int		step;
	t_ivec	delta;
	t_fvec	inc;

	i = 0;
	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	if (abs(delta.x) > abs(delta.y))
		step = abs(delta.x);
	else
		step = abs(delta.y);
	inc.x = delta.x / (float)step;
	inc.y = delta.y / (float)step;
	while (i <= step)
	{
		if (p1.x >= WIN_WID || p1.y >= WIN_HEI || p1.x < 0 || p1.y < 0)
			break ;
		mlx_put_pixel(image, p1.x, p1.y, color);
		p1.x += inc.x;
		p1.y += inc.y;
		i++;
	}
}

void	draw_square(mlx_image_t *image, t_ivec p, int size, int color)
{
	int	i;

	i = 0;
	size -= 1;
	while (i <= size)
	{
		draw_line(image, (t_fvec){p.x, p.y + i}, (t_fvec){p.x + size, p.y + i}, color);
		i++;
	}
	draw_line(image, (t_fvec){p.x, p.y}, (t_fvec){p.x + size, p.y}, 0xFFFFFFFF);
	draw_line(image, (t_fvec){p.x, p.y}, (t_fvec){p.x, p.y + size}, 0xFFFFFFFF);
	draw_line(image, (t_fvec){p.x + size, p.y}, (t_fvec){p.x + size, p.y + size}, 0xFFFFFFFF);
	draw_line(image, (t_fvec){p.x, p.y + size}, (t_fvec){p.x + size, p.y + size}, 0xFFFFFFFF);
}

void	draw_map(mlx_image_t *img, char **map)
{
	int		i;
	int		j;
	size_t	size;

	size = 0;
	while (map[size])
		size++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				draw_square(img, (t_ivec){j * UNIT, i * UNIT}, UNIT, 0x111111FF);
			else
				draw_square(img, (t_ivec){j * UNIT, i * UNIT}, UNIT, 0xEEEEEEFF);
			j++;
		}
		i++;
	}
}

void	draw_circle(mlx_image_t *image, t_fvec c, int rad, int color)
{
	int	x;
	int	y;

	x = -rad;
	while (x <= rad)
	{
		y = -rad;
		while (y <= rad)
		{
			if (x * x + y * y < rad * rad)
				if (c.x + x <= WIN_WID && c.y + y <= WIN_HEI && c.x + x > 0 && c.y + y > 0)
					mlx_put_pixel(image, c.x + x, c.y + y, color);
			y++;
		}
		x++;
	}
}

void	draw_player(mlx_image_t *image, t_player *player)
{
	t_fvec	p;

	get_dir_vector(&p.x, &p.y, player->angle);
	p.x = player->dir.x * 10 + player->pos.x;
	p.y = player->dir.y * 10 + player->pos.y;
	draw_circle(image, player->pos, 5, 0xFF0000FF);
	draw_line(image, player->pos, p, 0xFF0000FF);
}

void	draw_rays(mlx_image_t *image, t_player *p, char **map_data, int color)
{
	int	i;
	int	wall;
	int	side;
	t_fvec	dir;
	t_fvec	delta;
	t_fvec	len;
	t_fvec	intersec;
	t_fvec	pos;
	t_ivec	map;
	t_ivec	step;
	float	alpha;
	float	distance = 0;
//	int	draw_s;
//	int	draw_e;
//	int	h;

	i = 0;
	pos.x = p->pos.x / UNIT;
	pos.y = p->pos.y / UNIT;
	alpha = p->angle - ((FOV / 2) * M_PI / 180);
	if (alpha < 0)
		alpha += 2 * M_PI;
	else if (alpha > 2 * M_PI)
		alpha -= 2 * M_PI;
	while (i < WIN_WID)
	{
		wall = 0;
		get_dir_vector(&dir.x, &dir.y, alpha);
		delta.x = sqrt(1 + (dir.y * dir.y) / (dir.x * dir.x));
		delta.y = sqrt(1 + (dir.x * dir.x) / (dir.y * dir.y));
		map.x = pos.x;
		map.y = pos.y;
		if (dir.x < 0)
		{
			step.x = -1;
			len.x = (p->pos.x  - (float)map.x * UNIT) * delta.x;
		}
		else
		{
			step.x = 1;
			len.x = ((float)(map.x + 1) * UNIT - p->pos.x) * delta.x;
		}
		if (dir.y < 0)
		{
			step.y = -1;
			len.y = (p->pos.y - (float)map.y * UNIT) * delta.y;
		}
		else
		{
			step.y = 1;
			len.y = ((float)(map.y + 1) * UNIT - p->pos.y) * delta.y;
		}
		while (!wall && distance < DOF)
		{
			if (len.x < len.y)
			{
				map.x += step.x;
				distance = len.x;
				len.x += delta.x * UNIT;
				side = 0;
			}
			else
			{
				map.y += step.y;
				distance = len.y;
				len.y += delta.y * UNIT;
				side = 1;
			}
			if (map_data[map.y] && map_data[map.y][map.x] == '1')
				wall = 1;
		}

		if (wall)
		{
			if (side == 0)
				distance -= 0;
			else
				distance -= 0;
			intersec.x = p->pos.x + (dir.x * distance);
			intersec.y = p->pos.y + (dir.y * distance);
			draw_line(image, (t_fvec){p->pos.x, p->pos.y}, (t_fvec){intersec.x, intersec.y}, color);
	//		h = (int)(WIN_WID / distance);
	//		draw_s = -h / 2 + WIN_WID / 2;
	//		if (draw_s < 0)
	//			draw_s = 0;
	//		draw_e = h / 2 + WIN_WID / 2;
	//		if (draw_e >= WIN_WID)
	//			draw_e = WIN_WID - 1;
	//		if (side == 1)
	//			color = 0xFF0000FF;
	//		else
	//			color = 0x00FF00FF;
	//		draw_line(image, (t_fvec){i, draw_s}, (t_fvec){i, draw_e}, color);
		}
		else
		{
			dir.x *= DOF;
			dir.y *= DOF;
			draw_line(image, (t_fvec){p->pos.x, p->pos.y}, (t_fvec){p->pos.x + dir.x, p->pos.y + dir.y}, 0xFF000022);
		}
		alpha += (FOV * M_PI / 180) / WIN_WID;
		i++;
	}
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
	draw_rays(data->image_p, data->player, data->map, 0x00CC00FF);
	draw_player(data->image_p, data->player);
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

	if (ac != 2)
		return (1);
	atexit(lek);
	(void)ac;
	(void)av;
	init_data(&data, av[1]);
	draw_map(data.image, data.map);
	draw_player(data.image_p, data.player);
	setup_hooks(&data);
	//printf("%f\n", data.mlx->delta_time);
	//printf("%f\n", 1.0 / data.mlx->delta_time);
	mlx_loop(data.mlx);
	clean_all(&data);
}
