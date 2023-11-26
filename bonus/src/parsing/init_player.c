/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 14:53:48 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/26 23:54:03 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static float	get_player_angle(char p)
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
		data->player = ft_malloc(sizeof(t_player), data);
		data->player->angle = get_player_angle(line[x]);
		data->player->speed = UNIT / 10;
		data->player->pos.x = x * UNIT + UNIT / 2;
		data->player->pos.y = y * UNIT + UNIT / 2;
		data->player->dir.x = cos(data->player->angle);
		data->player->dir.y = sin(data->player->angle);
	}
	else
	{
		free(line);
		ft_error(PLAYER_DUP, data);
	}
}

static void	init_enemy(char *line, int x, int y, t_data *data)
{
	if (data->enemy == NULL)
	{
		data->enemy = ft_malloc(sizeof(t_sprite), data);
		data->enemy->tex_max = 5; //tmp
		data->enemy = ft_malloc(data->enemy->tex_max * sizeof(mlx_texture_t *), data);
		data->enemy->pos.x = x * UNIT + UNIT / 2;
		data->enemy->pos.y = y * UNIT + UNIT / 2;
		//data->enemy->textures[0] == mlx_load_png();
		//data->enemy->textures[1] == mlx_load_png();
		//data->enemy->textures[2] == mlx_load_png();
		//data->enemy->textures[3] == mlx_load_png();
		//data->enemy->textures[4] == mlx_load_png();
		// check textures
	}
	else
	{
		free(line);
		ft_error(ENEMY_DUP, data);
	}
}

t_entity	*add_node(t_data *data)
{
	t_entity	*ptr;

	ptr = ft_malloc(sizeof(t_entity), data);
	ptr->sp = ft_malloc(sizeof(t_sprite), data);
	ptr->sp->alm_texture = NULL; 
	ptr->sp->alm_texture = mlx_load_png("/Users/anchaouk/Desktop/main/textures/almondw.png");
	if (ptr->sp->alm_texture == NULL)
	{
		puts("cannot loaded"); // tmp
		exit (1);
	}
	ptr->next = NULL;
	return (ptr);
}

static void	fill_entity(t_data *data, int x, int y, char *line)
{
	t_entity	*head;

	head = data->entity;
	(void)line; // for later freeing in case of error
	if (data->entity == NULL)
	{	
		data->entity = add_node(data);
		data->entity->sp->pos.x = x * UNIT + UNIT / 2;
		data->entity->sp->pos.y = y * UNIT + UNIT / 2;
		return ;
	}
	else
	{
		while (data->entity->next)
			data->entity = data->entity->next;
		data->entity->next =  add_node(data);
		data->entity = data->entity->next;
		data->entity->next = NULL;
	}
	data->entity->sp->pos.x = x * UNIT + UNIT / 2;
	data->entity->sp->pos.y = y * UNIT + UNIT / 2;
	data->entity = head;
}

void	check_player(t_data *data, char *map_line, int y)
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
			fill_entity(data, x, y, map_line);
	}
}
