/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/04/05 19:14:23 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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

/*
char	*get_next_line(int fd)
{
	static t_char_queue	*queue[MAX_FD];
	ssize_t				bytes_read;
	char* line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (char_queue_contains(queue[fd], '\n'))
		return (move_line_from_queue(&queue[fd]));
	bytes_read = load_queue(&queue[fd], fd);
	if (bytes_read < 0)
	{
		char_queue_clear(&queue[fd]);
		return (NULL);
	}
	if (bytes_read == 0 && !queue[fd])
		return (NULL);
	while (bytes_read == BUFFER_SIZE && !char_queue_contains(queue[fd], '\n'))
		bytes_read = load_queue(&queue[fd], fd);
	if (bytes_read < 0)
	{
		char_queue_clear(&queue[fd]);
		return (NULL);
	}
	return (move_line_from_queue(&queue[fd]));
}
*/

#define ARBITRARY_POSITIVE_VALUE 1

ssize_t move_until_newline(char** line_ref, char* remaining)
{
	char *newline_pointer;

	*line_ref = ft_strdup(remaining);
	newline_pointer = ft_strchr(*line_ref, '\n');
	if (newline_pointer == NULL)
	{
		*remaining = '\0';
		return 0;
	}
	else
	{
		ft_memcpy(remaining, newline_pointer, ft_strlen(newline_pointer) + 1);
		newline_pointer[1] = '\0';
		return 0;
	}
}

ssize_t load_buffer(char* line, char* remaining, int fd)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read = read(0, 0, 0);
	return bytes_read;
}

char	*get_next_line(int fd)
{
	static char remaining[BUFFER_SIZE + 1];
	char* line = NULL;
	ssize_t bytes_read;

	if (*remaining)
		move_until_newline(&line, remaining);

	bytes_read = ARBITRARY_POSITIVE_VALUE;
	while (bytes_read && !ft_strchr(line, '\n') && *remaining == '\0')
		bytes_read = load_buffer(line, remaining, fd);

	if (*line == '\0')
	{
		free(line);
		line = NULL;
	}	
	return line;
}
