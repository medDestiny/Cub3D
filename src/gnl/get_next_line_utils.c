/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:34:03 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 11:24:49 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

int	ft_newline(t_list *lst, char **ptr)
{
	int	i;

	i = 0;
	while (lst && lst->content && lst->content[i])
	{
		if (lst->content[i] == '\n')
		{
			*ptr = &lst->content[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int	get_size(t_list *lst)
{
	int	i;
	int	size;

	size = 0;
	while (lst && lst->content)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				size++;
				break ;
			}
			size++;
			i++;
		}
		lst = lst->next;
	}
	return (size);
}

int	ft_lstnew(t_list **lst, long long size)
{
	t_list	*new;

	new = *lst;
	if (!new)
	{
		new = (t_list *)ft_calloc(1, sizeof(t_list));
		if (!new)
			return (-1);
	}
	new->content = (char *)ft_calloc(size + 1, sizeof(char));
	if (!new->content)
		return (-1);
	*lst = new;
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	size_t	j;
	void	*p;

	i = size * count;
	if ((count && (i / count) != size) || (size && (i / size) != count))
		return (0);
	p = malloc((count * size));
	if (!p)
		return (NULL);
	j = 0;
	while (j < (count * size))
	{
		((unsigned char *)p)[j] = 0;
		j++;
	}
	return (p);
}
