/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:10:36 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 11:21:49 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	s += i;
	c = (unsigned char)c;
	if (c == 0)
		return ((char *)s);
	while (i >= 0)
	{
		if (*s == c)
			return ((char *)s);
		i--;
		s--;
	}
	return (0);
}
