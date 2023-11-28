/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:53:48 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/28 12:44:57 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

static void	init_player(char *line, int x, int y, t_data *data)
{
	if (data->player == NULL)
	{
		data->player = ft_malloc(sizeof(t_player), data, clean_parsing);
		data->player->angle = get_player_angle(line[x]);
		data->player->speed = UNIT / 10;
		data->player->sanity = SANITY;
		data->player->pos.x = x * UNIT + UNIT / 2;
		data->player->pos.y = y * UNIT + UNIT / 2;
		data->player->dir.x = cos(data->player->angle);
		data->player->dir.y = sin(data->player->angle);
	}
	else
	{
		free(line);
		ft_error(PLAYER_DUP, data, clean_parsing);
	}
}

static void	init_enemy(char *line, int x, int y, t_data *data)
{
	if (data->enemy == NULL)
	{
		data->enemy = ft_malloc(sizeof(t_sprite), data, clean_parsing);
		data->enemy->state = ACTIVE;
		data->enemy->tex_max = 17; //tmp
		data->enemy->tex_index = 0;
		data->enemy->texture = ft_malloc(data->enemy->tex_max * sizeof(mlx_texture_t *), data, clean_parsing);
		data->enemy->pos.x = x * UNIT + UNIT / 2;
		data->enemy->pos.y = y * UNIT + UNIT / 2;
		data->enemy->texture[0] = mlx_load_png("enemy/scp01.png");
		data->enemy->texture[1] = mlx_load_png("enemy/scp02.png");
		data->enemy->texture[2] = mlx_load_png("enemy/scp03.png");
		data->enemy->texture[3] = mlx_load_png("enemy/scp04.png");
		data->enemy->texture[4] = mlx_load_png("enemy/scp05.png");
		data->enemy->texture[5] = mlx_load_png("enemy/scp06.png");
		data->enemy->texture[6] = mlx_load_png("enemy/scp07.png");
		data->enemy->texture[7] = mlx_load_png("enemy/scp08.png");
		data->enemy->texture[8] = mlx_load_png("enemy/scp09.png");
		data->enemy->texture[9] = mlx_load_png("enemy/scp10.png");
		data->enemy->texture[10] = mlx_load_png("enemy/scp11.png");
		data->enemy->texture[11] = mlx_load_png("enemy/scp12.png");
		data->enemy->texture[12] = mlx_load_png("enemy/scp13.png");
		data->enemy->texture[13] = mlx_load_png("enemy/scp14.png");
		data->enemy->texture[14] = mlx_load_png("enemy/scp15.png");
		data->enemy->texture[15] = mlx_load_png("enemy/scp16.png");
		data->enemy->texture[16] = mlx_load_png("enemy/scp17.png");
		// check textures
	}
	else
	{
		free(line);
		ft_error(ENEMY_DUP, data, clean_parsing);
	}
}

t_sp_list	*add_node(t_data *data, char *line)
{
	t_sp_list	*ptr;

	ptr = ft_malloc(sizeof(t_sp_list), data, clean_parsing);
	ptr->sp = ft_malloc(sizeof(t_sprite), data, clean_parsing);
	ptr->sp->state = ACTIVE;
	ptr->sp->tex_max = 1;
	ptr->sp->tex_index = 0;
	ptr->sp->texture = ft_malloc(sizeof(mlx_texture_t *), data, clean_parsing);
	ptr->sp->texture[0] = mlx_load_png("textures/almondw.png");
	if (ptr->sp->texture[0] == NULL)
	{
		free(line);
		ft_error(MLX_ERR, data, clean_parsing);
	}
	ptr->next = NULL;
	return (ptr);
}

static void	fill_sprites(t_data *data, int x, int y, char *line)
{
	t_sp_list	*tmp;

	tmp = data->sprites;
	if (data->sprites == NULL)
	{
		tmp = add_node(data, line);
		data->sprites = tmp;
	}
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next =  add_node(data, line);
		tmp = tmp->next;
	}
	tmp->sp->pos.x = x * UNIT + UNIT / 2;
	tmp->sp->pos.y = y * UNIT + UNIT / 2;
	tmp->next = NULL;
}

void	check_entities(t_data *data, char *map_line, int y)
{
	int	x;

	x = -1;
	while (map_line[++x])
	{
		if (map_line[x] && (map_line[x] == 'N' || map_line[x] == 'S'
				|| map_line[x] == 'E' || map_line[x] == 'W'))
			init_player(map_line, x, y, data);
		else if (map_line[x] == 'e')
			init_enemy(map_line, x, y, data);
		else if (map_line[x] == 'a')
			fill_sprites(data, x, y, map_line);
	}
}

