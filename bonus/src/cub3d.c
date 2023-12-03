/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 18:33:10 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 15:58:32 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	// temp
	h = mlx_load_png("assets/textures/hud3.png");

	data->mlx = mlx_init(WIN_WID, WIN_HEI, "cub3D", true);
	if (!data->mlx)
		ft_error(MLX_ERR, data, clean_parsing);
	data->image = mlx_new_image(data->mlx, WIN_WID, WIN_HEI);
	if (!data->image)
		ft_error(MLX_ERR, data, clean_all);

	// save a copy of the map for resetting purposes
	int	y;

	y = 0;
	while (data->map[y])
	{
		data->saved_map[y] = ft_strdup(data->map[y]);
		y++;
	}

	// these are for the bonus
	data->astar = (t_astar *)ft_malloc(sizeof(t_astar), data, clean_all);
	data->zbuffer = (float *)ft_malloc(WIN_WID * sizeof(float), data, clean_all);
	data->astar->max = get_max_size(data->map);
	data->astar->grid = init_nodes(data->astar->max, data);
	data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));

	data->game = ft_malloc(sizeof(t_game), data, clean_all);

	data->game->width = WIN_WID;
	data->game->height = WIN_HEI;

	//	init game scenes
	init_win_scene(data);
	init_death_scene(data);
	init_insanity_scene(data);
	init_pause_scene(data);
	init_menu_scene(data);

	data->game->state = MENU;
	data->game->score = NULL;
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		ft_error(MLX_ERR, data, clean_all);
}

void	check_for_entities(t_data *data)
{
	t_sp_list	*s;

	if (fabs(data->player->pos.x - data->goal->pos.x) < UNIT / 2
		&& fabs(data->player->pos.y - data->goal->pos.y) < UNIT / 2)
		data->game->state = WIN;
	if ((int)(data->player->pos.x / UNIT) == (int)(data->enemy->pos.x / UNIT)
		&& (int)(data->player->pos.y / UNIT) == (int)(data->enemy->pos.y / UNIT))
		data->game->state = DEATH;
	else if (data->player->sanity == 0)
		data->game->state = INSANITY;
	if (data->game->state != PLAYING)
		return ;
	s = data->sprites;
	while (s)
	{
		if (s->sp->state == ACTIVE
			&& fabs(data->player->pos.x - s->sp->pos.x) < UNIT / 2
			&& fabs(data->player->pos.y - s->sp->pos.y) < UNIT / 2
			&& data->player->sanity < SANITY)
		{
			data->player->sanity += min(SANITY - data->player->sanity, 400);
			s->sp->state = INACTIVE;
		}
		s = s->next;
	}
}

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
		data->astar->path = find_path(data, fvec_to_ivec(data->player->pos), fvec_to_ivec(data->enemy->pos));
		if (data->player->sanity - 100 >= 0)
			data->player->sanity -= 100;
		last_time = mlx_get_time();
	}
	move_player(data);
	//move_enemy(data->astar, data->enemy, data->player->speed * data->mlx->delta_time);
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
	//system("killall afplay");
	system("leaks cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_data	data;

	atexit(lek); // moooohsiine

	//system("afplay ~/goinfre/scp/rain.mp3 -v 0.2 &");
	parser(av, ac, &data);
	init_data(&data);
	render(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx);
	clean_all(&data);
}
