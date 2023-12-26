/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/26 15:27:20 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

char	*get_next_line(int fd)
{
	static t_char_queue	*queue;
	ssize_t			bytes_read;

	if (queue_contains(queue, '\n'))
		return (move_line_from_queue(&queue));
	bytes_read = load_queue(&queue, fd, BUFFER_SIZE);
	while (bytes_read == BUFFER_SIZE && !queue_contains(queue, '\n'))
		bytes_read = load_queue(&queue, fd, BUFFER_SIZE);
	if (bytes_read == 0 && !queue)
		return (NULL);
	return (move_line_from_queue(&queue));
}

char	*move_line_from_queue(t_char_queue **q)
{
	char		*line;
	const char	*line_start;

	line = malloc(1 + line_length(*q));
	line_start = line;
	while (*q)
	{
		*line = char_queue_pop(q);
		line++;
		if (*(line - 1) == '\n')
			break ;
	}
	*line = '\0';
	return ((char *)line_start);
}

ssize_t	load_queue(t_char_queue **q, int fd, size_t buffer_size)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	ssize_t	i;

	bytes_read = read(fd, buffer, buffer_size);
	i = 0;
	if (bytes_read <= 0)
	{
		return (0);
	}
	while (i < bytes_read)
	{
		char_queue_push(q, buffer[i]);
		i++;
	}
	return (bytes_read);
}
