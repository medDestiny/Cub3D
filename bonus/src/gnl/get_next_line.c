/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:33:55 by mmisskin          #+#    #+#             */
/*   Updated: 2023/10/23 11:24:40 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

void	read_n_fill(t_list **lst, int fd, int *r)
{
	t_list	*head;
	int		err;

	head = NULL;
	while (*r > 0 && !ft_newline(*lst, &(*lst)->ptr))
	{
		if (!*lst)
			err = ft_lstnew(&*lst, BUFFER_SIZE);
		else
			err = ft_lstnew(&(*lst)->next, BUFFER_SIZE);
		if (err == -1)
		{
			*r = -1;
			return ;
		}
		if (!head)
			head = *lst;
		if ((*lst)->next)
			*lst = (*lst)->next;
		*r = read(fd, (*lst)->content, BUFFER_SIZE);
	}
	if (head)
		*lst = head;
}

void	extract_line(t_list *lst, char *line)
{
	int	i;
	int	j;

	j = 0;
	while (lst && lst->content)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				line[j] = '\n';
				return ;
			}
			line[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
}

char	*ft_clean(t_list **lst)
{
	t_list	*next;

	next = (*lst)->next;
	free((*lst)->content);
	free(*lst);
	*lst = next;
	return (0);
}

void	clean_lst(t_list **lst)
{
	int		i;

	while (*lst)
	{
		if ((*lst)->ptr && *(*lst)->ptr == '\n')
		{
			ft_lstnew(&(*lst)->next, ft_strlen((*lst)->ptr));
			(*lst)->ptr++;
			break ;
		}
		ft_clean(lst);
	}
	if (!*lst)
		return ;
	i = -1;
	while ((*lst)->ptr[++i])
		(*lst)->next->content[i] = (*lst)->ptr[i];
	ft_clean(lst);
}

// This is our main function in which we'll read from the fd
// given as a parameter.
//
// 1st Step: - reading from the fd and unsing our list's node
// 			 as a buffer every time we read.
// 			 - we check every node for a new-line character
// 			 and we compare read's return with 0.
//
// 2nd Step: counting the total length of our line, and allocating it.
//
// 3rd Step: - traversing out list's nodes to collect all the
// 			 characters for our line including '\n'.
//
// 4th Step: - cleaning all the nodes that we already cloned
// 			 to our variable line.
// 			 - if a node containes more characters after '\n'
// 			 we clone those characters to a new one.
// 			 - if the new node containes nothing but a '\0' we simply delete it.
//
// After those steps our list should only contain the unreturned
// characters that will be needed to form the next line.

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;
	int				r;
	int				size;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	r = 1;
	read_n_fill(&lst, fd, &r);
	if ((r == 0 && !lst->content[0]) || r == -1)
		return (ft_clean(&lst));
	size = get_size(lst);
	line = (char *)ft_calloc(size + 1, sizeof(char));
	if (!line)
		return (0);
	line[size] = '\0';
	extract_line(lst, line);
	clean_lst(&lst);
	if (lst && !lst->content[0])
		ft_clean(&lst);
	return (line);
}
