/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anchaouk <anchaouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 11:02:54 by mmisskin          #+#    #+#             */
/*   Updated: 2023/11/05 21:50:04 by anchaouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<stdlib.h>
# include<unistd.h>

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	*ft_calloc_l(size_t num, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_bzero_l(void *s, size_t n);

#endif
