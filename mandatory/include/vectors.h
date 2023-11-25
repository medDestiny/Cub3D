/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:36:16 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/16 11:41:03 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_fvec
{
	float	x;
	float	y;
}	t_fvec;

typedef struct s_ivec
{
	int	x;
	int	y;
}	t_ivec;

//		Conversion from fvec to ivec
t_ivec	fvec_to_ivec(t_fvec x);

#endif
