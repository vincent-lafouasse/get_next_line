/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/01/01 16:28:50 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <sys/syslimits.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

char	*get_next_line(int fd)
{
	static t_char_queue	*queue[OPEN_MAX];
	ssize_t				bytes_read;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (char_queue_contains(queue[fd], '\n'))
		return (move_line_from_queue(&queue[fd]));
	bytes_read = load_queue(&queue[fd], fd, BUFFER_SIZE);
	while (bytes_read == BUFFER_SIZE && !char_queue_contains(queue[fd], '\n'))
		bytes_read = load_queue(&queue[fd], fd, BUFFER_SIZE);
	if (bytes_read <= 0 && !queue[fd])
		return (NULL);
	return (move_line_from_queue(&queue[fd]));
}

char	*move_line_from_queue(t_char_queue **q)
{
	char		*line;
	const char	*line_start;

	if (!q)
		return (NULL);
	line = malloc(1 + line_length(*q));
	if (!line)
		return (NULL);
	line_start = line;
	while (*q)
	{
		*line = char_queue_pop_front(q);
		line++;
		if (*(line - 1) == '\n')
			break ;
	}
	*line = '\0';
	return ((char *)line_start);
}

ssize_t	load_queue(t_char_queue **q, int fd, size_t buffer_size)
{
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	i;

	buffer = malloc(buffer_size);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, buffer_size);
	i = 0;
	if (bytes_read <= 0)
	{
		free(buffer);
		return (0);
	}
	while (i < bytes_read)
	{
		char_queue_push_back(q, buffer[i]);
		i++;
	}
	free(buffer);
	return (bytes_read);
}
