/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:32:23 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/03 18:35:11 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vectors.h"

typedef struct s_data	t_data;

typedef enum s_p_state
{
	ALIVE,
	DEAD,
	INSANE,
	WON
}	t_p_state;

typedef struct s_mvm
{
	short int	front;
	short int	back;
	short int	left;
	short int	right;
	short int	rotate;
}	t_mvm;

typedef struct s_player
{
	t_p_state	state;
	t_fvec		pos;
	t_fvec		dir;
	t_mvm		move;
	float		angle;
	float		speed;
	int			sanity;
	int			score;
}	t_player;

//		Movement registration
void	initiate_move(t_player *p, float speed, char **map, float angle);
void	move_player(t_data *data);

#endif
