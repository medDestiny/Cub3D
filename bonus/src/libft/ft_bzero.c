/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:36:38 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/05 21:49:13 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_bzero_l(void *s, size_t n)
{
	size_t	i;
	int		null;
	char	*str;

	i = 0;
	null = '\0';
	str = s;
	while (i < n)
	{
		str[i] = null;
		i++;
	}
}
