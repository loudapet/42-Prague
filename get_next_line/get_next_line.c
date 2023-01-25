/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plouda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 09:38:21 by plouda            #+#    #+#             */
/*   Updated: 2023/01/25 15:37:56 by plouda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_next_line(char *text)
{
	unsigned int	i;
	unsigned int	j;
	char			*next_line;

	i = 0;
	j = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	next_line = malloc(ft_strlen(text) + 1 - i);
	if (!next_line)
		return (NULL);
	i++;
	while (text[i] != '\0')
		next_line[j++] = text[i++];
	next_line[j] = '\0';
	free(text);
	return (next_line);
}

char	*get_current_line(char *text)
{
	char			*line;
	unsigned int	i;

	i = 0;
	if (!*text)
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (text[i] != '\0' && text[i] != '\n')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *text)
{
	char	*buf;
	int		bytes_read;

	bytes_read = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (!ft_strchr_custom(text, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = 0;
		text = ft_strjoin_custom(text, buf);
	}
	free(buf);
	return (text);
}

char	*get_next_line(int fd)
{
	static char	*text;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	text = read_file(fd, text);
	if (!text)
		return (NULL);
	line = get_current_line(text);
	text = set_next_line(text);
	return (line);
}
