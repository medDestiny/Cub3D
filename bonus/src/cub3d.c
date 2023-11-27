/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/27 22:41:23 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	// temp
	h = mlx_load_png("textures/hud1.png");

	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	if (!data->mlx)
		ft_error(MLX_ERR, data);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	if (!data->image)
		ft_error(MLX_ERR, data);

	// these are for the bonus
	data->astar = (t_astar *)ft_malloc(sizeof(t_astar), data);
	data->zbuffer = (float *)ft_malloc(WIN_WID * sizeof(float), data);
	data->astar->max = get_max_size(data->map);
	data->astar->grid = init_nodes(data->astar->max, data);
	data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));

	data->game.width = WIN_WID;
	data->game.height = WIN_HEI;
	data->game.state = PLAYING;
	data->player->sanity = 1000;
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data);
}

void	reset_game(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->saved_map[y])
	{
		x = 0;
		while (data->saved_map[x])
		{
			x++;
		}
		y++;
	}
}

void	move_enemy(t_astar *astar, t_sprite *e, t_player *p);

void	check_for_entities(t_data *data)
{
	t_sp_list	*s;

	if (fabs(data->player->pos.x - data->enemy->pos.x) < UNIT / 2
		&& fabs(data->player->pos.y - data->enemy->pos.y) < UNIT / 2)
		data->game.state = LOSE;
	else if (data->player->sanity == 0)
		data->game.state = LOSE;
	s = data->sprites;
	while (s)
	{
		if (fabs(data->player->pos.x - s->sp->pos.x) < UNIT / 4
			&& fabs(data->player->pos.y - s->sp->pos.y) < UNIT / 4)
			data->player->sanity += 400;
		// delete sprite
		s = s->next;
	}
}

void	update(t_data *data)
{
	static int	time; // for bonus

	if (time > 20)
	{
		data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));
		data->player->sanity -= 100;
		time = 0;
	}
	move_player(data);
	move_enemy(data->astar, data->enemy, data->player);
	check_for_entities(data);
	time++; // better use mlx_get_time
}

void	render(t_data *data)
{
	t_sp_list	*sp;

	if (data->game.state == PLAYING)
	{
		//draw_player(data->image_p, data->player);
		//draw_circle(data->image_p, data->enemy->pos, 5, 0x111111FF);
		draw_scene(data);
		draw_sprite(data, data->enemy);
		sp = data->sprites;
		while (sp)
		{
			draw_sprite(data, sp->sp);
			sp = sp->next;
		}
		//draw_hud(data);
	}
	else if (data->game.state == LOSE)
	{
		reset_game(data);
		puts("YOU LOST");
	}
	else if (data->game.state == WIN)
	{
		puts("YOU WON");
	}
	else if (data->game.state == MENU)
	{

	}
}

void	setup_hooks(t_data *data)
{
	mlx_key_hook(data->mlx, key_hooks, data);
	mlx_resize_hook(data->mlx, resize_hook, data);
	mlx_cursor_hook(data->mlx, cursor_rotate, data);
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
