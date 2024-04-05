/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/04/05 18:09:59 by poss             ###   ########.fr       */
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

typedef struct
{
	char* self;

}	t_dynamic_string;

ssize_t append_until_newline(char* line, char* remaining);
ssize_t load_buffer(char* line, char* remaining, int fd);

char	*get_next_line(int fd)
{
	char* line;
	static char* remaining;

	if (remaining && *remaining)
		append_until_newline(line, remaining);

	while (*remaining == '\0')
		load_buffer(line, remaining, fd);

	return line;
}
