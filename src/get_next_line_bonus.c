/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/01/04 18:14:29 by vlafouas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 512
#endif

/* using the output of `ulimit -aH`, I do not like this,
	this is probably not portable*/
#define FD_HARD_LIMIT 1048576

char	*get_next_line(int fd)
{
	static t_char_queue	*queue[FD_HARD_LIMIT] = {0};
	ssize_t				bytes_read;

	if (fd < 0 || fd >= FD_HARD_LIMIT)
		return (NULL);
	if (char_queue_contains(queue[fd], '\n'))
		return (move_line_from_queue(queue + fd));
	bytes_read = load_queue(queue + fd, fd, BUFFER_SIZE);
	while (bytes_read == BUFFER_SIZE && !char_queue_contains(queue[fd], '\n'))
		bytes_read = load_queue(queue + fd, fd, BUFFER_SIZE);
	if (bytes_read < 0)
		return (char_queue_clear(queue + fd), NULL);
	if (bytes_read == 0 && !queue[fd])
		return (NULL);
	return (move_line_from_queue(queue + fd));
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
	bool	push_status;

	buffer = malloc(buffer_size);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, buffer_size);
	i = 0;
	while (i < bytes_read)
	{
		push_status = char_queue_push_back(q, buffer[i]);
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

void	char_queue_clear(t_char_queue **q)
{
	if (!q)
		return ;
	while (*q)
		char_queue_pop_front(q);
}
