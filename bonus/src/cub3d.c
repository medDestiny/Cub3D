/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 18:04:19 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	if (!data->mlx)
		ft_error(MLX_ERR, data);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	if (!data->image)
		ft_error(MLX_ERR, data);
	data->image_p = mlx_new_image(data->mlx, WIN_WID, WIN_HEI); // temporairly
	if (!data->image_p)
		ft_error(MLX_ERR, data);
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
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data);
	if (mlx_image_to_window(data->mlx, data->image_p, 0, 0) == -1)
		ft_error(MLX_ERR, data);
}

void	move_enemy(t_astar *astar, t_sprite *e, t_player *p);

void	update(t_data *data)
{
	static int	time; // for bonus

	if (time > 20)
	{
		data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));
		time = 0;
	}
	move_player(data);
	move_enemy(data->astar, data->enemy, data->player);
	time++; // better use mlx_get_time
}

void	render(t_data *data)
{
	//draw_player(data->image_p, data->player);
	//draw_circle(data->image_p, data->enemy->pos, 5, 0x111111FF);
	draw_scene(data);
	//draw_sprite(data, data->enemy);
	//draw_hud(data);
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_hooks, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_close_hook(data->mlx, close_hook, data);
	mlx_loop_hook(data->mlx, hooks, data);
}

void	lek(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(lek); // moooohsiine

	parser(av, ac, &data);
	init_data(&data);
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	// clean_all(&data);
}
