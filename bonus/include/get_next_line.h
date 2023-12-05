/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisskin <mmisskin@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:53:18 by mmisskin          #+#    #+#             */
/*   Updated: 2023/12/05 12:19:45 by mmisskin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	char			*ptr;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_lstnew(t_list **lst, long long size);
int		get_size(t_list *lst);
int		ft_newline(t_list *lst, char **ptr);
void	read_n_fill(t_list **lst, int fd, int *r);
void	extract_line(t_list *lst, char *line);
void	clean_lst(t_list **lst);
char	*ft_clean(t_list **lst);
char	*get_next_line(int fd);

#endif
