/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:19 by poss              #+#    #+#             */
/*   Updated: 2024/01/18 01:59:11 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

/* using the output of `ulimit -aH`, I do not like this,
	this is probably not portable*/
#define FD_HARD_LIMIT 1048576

#ifndef MAX_FD
# define MAX_FD FD_HARD_LIMIT
#endif

char	*get_next_line(int fd)
{
	static t_char_queue	*queue[MAX_FD];
	ssize_t				bytes_read;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (char_queue_contains(queue[fd], '\n'))
		return (move_line_from_queue(&queue[fd]));
	bytes_read = load_queue(&queue[fd], fd, BUFFER_SIZE);
	if (bytes_read < 0)
		return (char_queue_clear(&queue[fd]), NULL);
	if (bytes_read == 0 && !queue[fd])
		return (NULL);
	while (bytes_read == BUFFER_SIZE && !char_queue_contains(queue[fd], '\n'))
		bytes_read = load_queue(&queue[fd], fd, BUFFER_SIZE);
	if (bytes_read < 0)
		return (char_queue_clear(&queue[fd]), NULL);
	return (move_line_from_queue(&queue[fd]));
}

char	*move_line_from_queue(t_char_queue **q_ptr)
{
	char		*line;
	const char	*line_start;

	line = malloc(1 + line_length(*q_ptr));
	if (!line || !q_ptr)
		return (free(line), char_queue_clear(q_ptr), NULL);
	line_start = line;
	while (*q_ptr)
	{
		*line = char_queue_pop_front(q_ptr);
		line++;
		if (*(line - 1) == '\n')
			break ;
	}
	*line = '\0';
	return ((char *)line_start);
}

ssize_t	load_queue(t_char_queue **q_ptr, int fd, size_t buffer_size)
{
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	i;
	bool	push_status;

	buffer = malloc(buffer_size);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, buffer_size);
	i = 0;
	while (i < bytes_read)
	{
		push_status = char_queue_push_back(q_ptr, buffer[i]);
		if (!push_status)
		{
			bytes_read = -1;
			break ;
		}
		i++;
	}
	free(buffer);
	return (bytes_read);
}

size_t	line_length(const t_char_queue *q)
{
	size_t	len;

	len = 0;
	while (q)
	{
		len++;
		if (q->c == '\n')
			break ;
		q = q->next;
	}
	return (len);
}
