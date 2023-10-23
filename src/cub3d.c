/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 18:50:51 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	move_front(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] == 1 && map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] == 1)
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] != 1)
	{
		p->pos.x += pos.x;
	}
	if (map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] != 1)
	{
		p->pos.y += pos.y;
	}
}

void	move_back(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] == 1 && map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] == 1)
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] != 1)
	{
		p->pos.x -= pos.x;
	}
	if (map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] != 1)
	{
		p->pos.y -= pos.y;
	}
}

void	move_right(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] == 1 && map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] == 1)
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x + pos.x) / UNIT] != 1)
	{
		p->pos.x += pos.x;
	}
	if (map[(int)(p->pos.y + pos.y) / UNIT][(int)p->pos.x / UNIT] != 1)
	{
		p->pos.y += pos.y;
	}
}

void	move_left(t_player *p, char **map)
{
	t_fvec	pos;

	pos.x = p->dir.x * SPEED;
	pos.y = p->dir.y * SPEED;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] == 1 && map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] == 1)
		return ;
	if (map[(int)p->pos.y / UNIT][(int)(p->pos.x - pos.x) / UNIT] != 1)
	{
		p->pos.x -= pos.x;
	}
	if (map[(int)(p->pos.y - pos.y) / UNIT][(int)p->pos.x / UNIT] != 1)
	{
		p->pos.y -= pos.y;
	}
}

void	key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_delete_image(data->mlx, data->image);
		mlx_delete_image(data->mlx, data->image_p);
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
		exit(0);
	}
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
	if (keydata.key == MLX_KEY_data->player->move.right && keydata.action != MLX_RELEASE)
		data->player->angle += 5 * M_PI / 180;
	if (keydata.key == MLX_KEY_data->player->move.left && keydata.action != MLX_RELEASE)
		data->player->angle -= 5 * M_PI / 180;
	if (data->player->angle < 0)
		data->player->angle += 2 * M_PI;
	if (data->player->angle > 2 * M_PI)
		data->player->angle -= 2 * M_PI;
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
	//draw_rays(image_p, k_x, k_y, 0x00CC00FF);
	draw_player(data->image_p, data->player);
	mlx_image_to_window(data->mlx, data->image_p, 0, 0);
	//printf("FPS:%.0f\n", 1.0 / data->mlx->delta_time);
}

void	setup_hooks(t_data *data)
{
	//mlx_key_hook();
	mlx_loop_hook(data->mlx, hooks, data);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (1);
	(void)ac;
	(void)av;
	init_data(&data, av[1]);
	printf("player_pos = (%f, %f)\n", data.player->pos.x, data.player->pos.y);
	printf("player_angle = %f\n", data.player->angle * 180 / M_PI);
	draw_map(data.image, data.map);
	draw_player(data.image_p, data.player);
	setup_hooks(&data);
	//printf("%f\n", data.mlx->delta_time);
	//printf("%f\n", 1.0 / data.mlx->delta_time);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
}


//int		win_size = UNIT * GRIDSIZE * 2;
//int		m_x, m_y;
//float	k_x, k_y;
//int		front, back, left, right;
//double	angle;
//
//int	grid[GRIDSIZE][GRIDSIZE] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
//								{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 0, 0, 0, 0, 1, 0, 0, 1}, 
//								{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 1, 0, 0, 0, 0, 0, 0, 1}, 
//								{1, 0, 1, 0, 0, 2, 0, 0, 0, 1}, 
//								{1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };
//
//void	draw_line(mlx_image_t *image, int x1, int y1, int x2, int y2, int color)
//{
//	int	i;
//	int	dx;
//	int	dy;
//	int	step;
//	float	x_inc;
//	float	y_inc;
//	float	x_start;
//	float	y_start;
//
//	i = 0;
//	dx = x2 - x1;
//	dy = y2 - y1;
//	if (abs(dx) > abs(dy))
//		step = abs(dx);	
//	else
//		step = abs(dy);
//	x_inc = dx / (float)step;
//	y_inc = dy / (float)step;
//	x_start = x1;
//	y_start = y1;
//	while (i <= step)
//	{
//		if (x_start > win_size || y_start > win_size || x_start < 0 || y_start < 0)
//			break ;
//		mlx_put_pixel(image, x_start, y_start, color);
//		x_start += x_inc;
//		y_start += y_inc;
//		i++;
//	}
//}
//
//void	draw_square(mlx_image_t *image, int x, int y, int size, int outline, int color)
//{
//	int	i;
//
//	i = 0;
//	size -= 1;
//	if (color != -1)
//	{
//		while (i <= size)
//		{
//			draw_line(image, x, y + i, x + size, y + i, color);
//			i++;
//		}
//	}
//	draw_line(image, x, y, x + size, y, outline);
//	draw_line(image, x, y, x, y + size, outline);
//	draw_line(image, x + size, y, x + size, y + size, outline);
//	draw_line(image, x, y + size, x + size, y + size, outline);
//}
//
//void	draw_grid(mlx_image_t *image, int grid[GRIDSIZE][GRIDSIZE])
//{
//	int	i;
//	int	j;
//	int	x;
//	int	y;
//
//	i = 0;
//	x = 0;
//	y = 0;
//	while (i < GRIDSIZE)
//	{
//		j = 0;
//		while (j < GRIDSIZE)
//		{
//			if (grid[i][j] == 1)
//				draw_square(image, x, y, UNIT, 0xECF542FF, 0x0F0F0FFF);
//			else
//				draw_square(image, x, y, UNIT, 0xFFFFFFFF, 0xEEEEEEFF);
//			x += UNIT;
//			j++;
//		}
//		x = 0;
//		y += UNIT;
//		i++;
//	}
//}
//
//void	draw_circle(mlx_image_t *image, int cx, int cy, int rad, int color)
//{
//	int	x;
//	int	y;
//
//	x = -rad;
//	while (x <= rad)
//	{
//		y = -rad;
//		while (y <= rad)
//		{
//			if (x * x + y * y < rad * rad)
//				if (cx + x <= win_size && cy + y <= win_size && cx + x > 0 && cy + y > 0)
//					mlx_put_pixel(image, cx + x, cy + y, color);
//			y++;
//		}
//		x++;
//	}
//}
//
//mlx_t		*mlx;
//mlx_image_t	*image;
//mlx_image_t	*image_cur;
//mlx_image_t	*image_p;
//
//void	draw_player(mlx_image_t *image, int grid[GRIDSIZE][GRIDSIZE])
//{
//	int	i;
//	int	j;
//	int	x;
//	int	y;
//
//	j = 0;
//	while (j < GRIDSIZE)
//	{
//		i = 0;
//		while (i < GRIDSIZE)
//		{
//			if (grid[j][i] == 2)
//				break ;
//			i++;
//		}
//		if (i < GRIDSIZE && grid[j][i] == 2)
//			break ;
//		j++;
//	}
//	x = i * UNIT + (UNIT / 2);
//	y = j * UNIT + (UNIT / 2);
//	k_x = x;
//	k_y = y;
//	draw_circle(image, k_x, k_y, 5, 0xFF0000FF);
//}
//
////{
////	int	px, py;
////
////	px = k_x;
////	py = k_y;
////}
//
//void	mouse(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
//{
//	int	i, j;
//	(void)action;
//	(void)mods;
//	(void)param;
//	if (button == MLX_MOUSE_BUTTON_RIGHT && action == MLX_PRESS)
//	{
//		j = m_x / UNIT;
//		i = m_y / UNIT;
//		if (i < GRIDSIZE && j < GRIDSIZE && i >= 0 && j >= 0)
//		{
//			if (grid[i][j] == 0)
//				grid[i][j] = 1;
//			else
//				grid[i][j] = 0;
//		}
//		mlx_delete_image(mlx, image);
//		image = mlx_new_image(mlx, win_size, win_size);
//		draw_grid(image, grid);
//		mlx_image_to_window(mlx, image, 0, 0);
//		mlx_image_to_window(mlx, image_p, 0, 0);
//	}
//	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
//		printf("Left click\n");
//}
//
//void	mouse_cursor(double xpos, double ypos, void *param)
//{
//	if (image_cur)
//		mlx_delete_image(param, image_cur);
//	image_cur = mlx_new_image(param, win_size, win_size);
//	if (xpos > m_x)
//		angle += 0.07;
//	else
//		angle -= 0.07;
//	if (angle < 0)
//		angle += 2 * M_PI;
//	if (angle > 2 * M_PI)
//		angle -= 2 * M_PI;
//	m_x = xpos;
//	m_y = ypos;
//	draw_square(image_cur, xpos, ypos, 5, 0xFF0000FF, 0xFF0000FF);
//	mlx_image_to_window(param, image_cur, 0, 0);
//}
//
//void	key(mlx_key_data_t keydata, void *param)
//{
//	(void)param;
//	if (keydata.key == MLX_KEY_ESCAPE)
//	{
//		mlx_delete_image(mlx, image);
//		mlx_delete_image(mlx, image_cur);
//		mlx_delete_image(mlx, image_p);
//		mlx_close_window(mlx);
//		mlx_terminate(mlx);
//		exit(0);
//	}
//	if (keydata.key == MLX_KEY_W && keydata.action != MLX_RELEASE) 
//		front = 1;
//	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE) 
//		front = 0;
//	if (keydata.key == MLX_KEY_S && keydata.action != MLX_RELEASE)
//		back = 1;
//	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
//		back = 0;
//	if (keydata.key == MLX_KEY_A && keydata.action != MLX_RELEASE)
//		left = 1;
//	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
//		left = 0;
//	if (keydata.key == MLX_KEY_D && keydata.action != MLX_RELEASE)
//		right = 1;
//	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
//		right = 0;
//	if (keydata.key == MLX_KEY_RIGHT && keydata.action != MLX_RELEASE)
//		angle += 5 * M_PI / 180;
//	if (keydata.key == MLX_KEY_LEFT && keydata.action != MLX_RELEASE)
//		angle -= 5 * M_PI / 180;
//	if (angle < 0)
//		angle += 2 * M_PI;
//	if (angle > 2 * M_PI)
//		angle -= 2 * M_PI;
//}
//
//void	calc_inc(float *x, float *y, float angle)
//{
//	*x = cos(angle);
//	*y = sin(angle);
//}
//
//void	move_front()
//{
//	float	x, y;
//
//	calc_inc(&x, &y, angle);
//	x *= SPEED;
//	y *= SPEED;
//	if (grid[(int)k_y / UNIT][(int)(k_x + x) / UNIT] == 1 && grid[(int)(k_y + y) / UNIT][(int)k_x / UNIT] == 1)
//		return ;
//	if (grid[(int)k_y / UNIT][(int)(k_x + x) / UNIT] != 1)
//	{
//		k_x += x;
//	}
//	if (grid[(int)(k_y + y) / UNIT][(int)k_x / UNIT] != 1)
//	{
//		k_y += y;
//	}
//}
//
//void	move_back()
//{
//	float	x, y;
//
//	calc_inc(&x, &y, angle);
//	x *= SPEED;
//	y *= SPEED;
//	if (grid[(int)k_y / UNIT][(int)(k_x - x) / UNIT] == 1 && grid[(int)(k_y - y) / UNIT][(int)k_x / UNIT] == 1)
//		return ;
//	if (grid[(int)k_y / UNIT][(int)(k_x - x) / UNIT] != 1)
//	{
//		k_x -= x;
//	}
//	if (grid[(int)(k_y - y) / UNIT][(int)k_x / UNIT] != 1)
//	{
//		k_y -= y;
//	}
//}
//
//void	move_right()
//{
//	float	x, y;
//
//	calc_inc(&x, &y, angle + (M_PI / 2));
//	x *= SPEED;
//	y *= SPEED;
//	if (grid[(int)k_y / UNIT][(int)(k_x + x) / UNIT] == 1 && grid[(int)(k_y + y) / UNIT][(int)k_x / UNIT] == 1)
//		return ;
//	if (grid[(int)k_y / UNIT][(int)(k_x + x) / UNIT] != 1)
//	{
//		k_x += x;
//	}
//	if (grid[(int)(k_y + y) / UNIT][(int)k_x / UNIT] != 1)
//	{
//		k_y += y;
//	}
//}
//
//void	move_left()
//{
//	float	x, y;
//
//	calc_inc(&x, &y, angle + (M_PI / 2));
//	x *= SPEED;
//	y *= SPEED;
//	if (grid[(int)k_y / UNIT][(int)(k_x - x) / UNIT] == 1 && grid[(int)(k_y - y) / UNIT][(int)k_x / UNIT] == 1)
//		return ;
//	if (grid[(int)k_y / UNIT][(int)(k_x - x) / UNIT] != 1)
//	{
//		k_x -= x;
//	}
//	if (grid[(int)(k_y - y) / UNIT][(int)k_x / UNIT] != 1)
//	{
//		k_y -= y;
//	}
//}
//
//void	draw_rays(mlx_image_t *image, float px, float py, int color)
//{
//	int	i;
//	int	wall;
//	float	x;
//	float	y;
//	float	delta;
//	float	dx;
//	float	dy;
//	int	map_x;
//	int	map_y;
//	float	len_x;
//	float	len_y;
//	int	step_x;
//	int	step_y;
//	float	distance = 0;
//	float	intersec_x;
//	float	intersec_y;
//	float	pos_x;
//	float	pos_y;
//	int	draw_s;
//	int	draw_e;
//	int	side;
//	int	h;
//
//	i = 0;
//	pos_x = px / UNIT;
//	pos_y = py / UNIT;
//	delta = angle - ((FOV / 2) * M_PI / 180);
//	if (delta < 0)
//		delta += 2 * M_PI;
//	else if (delta > 2 * M_PI)
//		delta -= 2 * M_PI;
//	while (i < win_size)
//	{
//		wall = 0;
//		calc_inc(&x, &y, delta);
//		dx = sqrt(1 + (y * y) / (x * x));
//		dy = sqrt(1 + (x * x) / (y * y));
//		map_x = pos_x;
//		map_y = pos_y;
//		if (x < 0)
//		{
//			step_x = -1;
//			len_x = (px  - (float)map_x * UNIT) * dx;
//		}
//		else
//		{
//			step_x = 1;
//			len_x = ((float)(map_x + 1) * UNIT - px) * dx;
//		}
//		if (y < 0)
//		{
//			step_y = -1;
//			len_y = (py - (float)map_y * UNIT) * dy;
//		}
//		else
//		{
//			step_y = 1;
//			len_y = ((float)(map_y + 1) * UNIT - py) * dy;
//		}
//		while (!wall && distance < MAX_DISTANCE)
//		{
//			if (len_x < len_y)
//			{
//				map_x += step_x;
//				distance = len_x;
//				len_x += dx * UNIT;
//				side = 0;
//			}
//			else
//			{
//				map_y += step_y;
//				distance = len_y;
//				len_y += dy * UNIT;
//				side = 1;
//			}
//			if (grid[map_y][map_x] == 1)
//			{
//				wall = 1;
//			}
//		}
//
//		if (wall)
//		{
//			if (side == 0)
//				distance -= 0;
//			else
//				distance -= 0;
//			intersec_x = px + (x * distance);
//			intersec_y = py + (y * distance);
//			//draw_line(image, px, py, intersec_x, intersec_y, color);
//			h = (int)(win_size / distance);
//			draw_s = -h / 2 + win_size / 2;
//			if (draw_s < 0)
//				draw_s = 0;
//			draw_e = h / 2 + win_size / 2;
//			if (draw_e >= win_size)
//				draw_e = win_size - 1;
//			if (side == 1)
//				color = 0xFF0000FF;
//			else
//				color = 0x00FF00FF;
//			draw_line(image, i, draw_s, i, draw_e, color);
//		}
//		//else
//		//{
//		//	x *= MAX_DISTANCE;
//		//	y *= MAX_DISTANCE;
//		//	draw_line(image, px, py, px + x, py + y, 0xFF000022);
//		//}
//		delta += (FOV * M_PI / 180) / win_size;
//		i++;
//	}
//}
//
//void	hooks(void *param)
//{
//	float	x_inc = 0;
//	float	y_inc = 0;
//
//	(void)param;
//	calc_inc(&x_inc, &y_inc, angle);
//	x_inc *= 10;
//	y_inc *= 10;
//	if (front == 1)
//		move_front();
//	if (back == 1)
//		move_back();
//	if (left == 1)
//		move_left();
//	if (right == 1)
//		move_right();
//	if (image_p)
//		mlx_delete_image(mlx, image_p);
//	image_p = mlx_new_image(mlx, win_size, win_size);
//	draw_rays(image_p, k_x, k_y, 0x00CC00FF);
//	draw_line(image_p, k_x, k_y, k_x + x_inc, k_y + y_inc, 0xFF0000FF);
//	draw_circle(image_p, k_x, k_y, 5, 0xFF0000FF);
//	mlx_image_to_window(mlx, image_p, 0, 0);
//}
//
//int	main()
//{
//	mlx = mlx_init(win_size, win_size, "test", true);
//	image = mlx_new_image(mlx, win_size, win_size);
//	image_p = mlx_new_image(mlx, win_size, win_size);
//	draw_grid(image, grid);
//	draw_player(image_p, grid);
//	mlx_image_to_window(mlx, image, 0, 0);
//	mlx_image_to_window(mlx, image_p, 0, 0);
//
//	mlx_mouse_hook(mlx, mouse, image);
//	mlx_cursor_hook(mlx, mouse_cursor, mlx);
//	mlx_key_hook(mlx, key, mlx);
//	mlx_loop_hook(mlx, hooks, grid);
//
//	mlx_loop(mlx);
//	mlx_terminate(mlx);
//}
