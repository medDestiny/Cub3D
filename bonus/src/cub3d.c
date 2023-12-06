/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/06 11:16:10 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	update(t_data *data)
{
	static double	last_time;

	if (data->game->state != PLAYING)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	else
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	if (mlx_get_time() - last_time >= 1)
	{
		data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), \
		fvec_to_ivec(data->enemy->pos));
		if (data->player->sanity - 100 >= 0)
			data->player->sanity -= 100;
		last_time = mlx_get_time();
	}
	move_player(data);
	move_enemy(data->astar, data->enemy, data->map, \
	data->player->speed * data->mlx->delta_time);
	check_for_entities(data);
}

void	render(t_data *data)
{
	if (data->game->state == PLAYING)
		render_game(data);
	else if (data->game->state == DEATH)
		render_death(data);
	else if (data->game->state == INSANITY)
		render_insanity(data);
	else if (data->game->state == WIN)
		render_win(data);
	else if (data->game->state == MENU)
		render_menu(data);
	else if (data->game->state == PAUSED)
		render_pause(data);
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
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(lek);
	parser(av, ac, &data);
	init_game_data(&data);
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	clean_all(&data);
}
