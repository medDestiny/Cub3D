/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:06:39 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/05 21:50:23 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_calloc_l(size_t num, size_t size)
{
	void	*ptr;
	size_t	protect;

	protect = num * size;
	if ((num && (protect / num) != size) || (size && (protect / size) != num))
		return (0);
	ptr = malloc(protect);
	if (!ptr)
		return (0);
	ft_bzero_l(ptr, protect);
	return (ptr);
}
