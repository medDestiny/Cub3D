/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:19:41 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/25 17:22:41 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	insert(t_lst **lst, t_node *node, t_lst *new)
{
	t_lst	*hold;
	t_lst	*tmp;

	tmp = *lst;
	hold = NULL;
	while (tmp && tmp->node && tmp->node->g_goal < node->g_goal)
	{
		hold = tmp;
		tmp = tmp->next;
	}
	new->node = node;
	new->next = tmp;
	if (hold)
		hold->next = new;
	else
		*lst = new;
}

void	clean_list(t_lst **lst)
{
	t_lst	*next;

	while (lst && *lst)
	{
		next = (*lst)->next;
		free(*lst);
		*lst = next;
	}
}

void	lst_insert(t_lst **lst, t_node *node, t_data *data)
{
	t_lst	*tmp;
	t_lst	*new;

	tmp = *lst;
	new = (t_lst *)malloc(sizeof(t_lst));
	if (!new)
	{
		clean_list(lst);
		ft_error(MALLOC_ERR, data);
		return ;
	}
	if (!tmp)
	{
		*lst = new;
		tmp = *lst;
	}
	else
		return (insert(lst, node, new));
	tmp->node = node;
	tmp->next = NULL;
}

void	lst_del_one(t_lst **lst)
{
	t_lst	*next;

	if (!lst || !*lst)
		return ;
	next = (*lst)->next;
	free(*lst);
	*lst = next;
}
