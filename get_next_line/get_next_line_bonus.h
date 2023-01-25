/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:38:44 by plouda            #+#    #+#             */
/*   Updated: 2023/01/25 16:19:42 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*read_file(int fd, char *text);
char	*get_current_line(char *text);
char	*set_next_line(char *text);
size_t	ft_strlen(const char *c);
char	*ft_strchr_custom(const char *s, int c);
char	*ft_strjoin_custom(char *s1, char *s2);

#endif