/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:48:59 by anchaouk          #+#    #+#             */
/*   Updated: 2023/11/05 21:49:57 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	*protect(char const *s, unsigned int start)
{
	char	*ptr;

	ptr = NULL;
	if (start > ft_strlen(s))
	{
		ptr = ft_calloc_l(1, 1);
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	const char	*str;
	char		*ptr;

	i = 0;
	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (protect(s, start));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	str = &s[start];
	ptr = (char *)malloc(len * sizeof(char) + 1);
	if (!ptr)
		return (0);
	while (i < len && start < ft_strlen(s))
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
