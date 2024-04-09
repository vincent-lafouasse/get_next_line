/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/04/09 17:41:07 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

/* using the output of `ulimit -aH`, I do not like this,
        this is probably not portable*/
#define FD_HARD_LIMIT 1048576

#ifndef MAX_FD
#define MAX_FD FD_HARD_LIMIT
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
        while (bytes_read == BUFFER_SIZE && !char_queue_contains(queue[fd],
'\n')) bytes_read = load_queue(&queue[fd], fd); if (bytes_read < 0)
        {
                char_queue_clear(&queue[fd]);
                return (NULL);
        }
        return (move_line_from_queue(&queue[fd]));
}
*/

#define ARBITRARY_POSITIVE_VALUE 1

ssize_t move_until_newline(t_string* str_ref, char* src);
ssize_t load_buffer(t_string line, char* remaining, int fd);

char* get_next_line(int fd)
{
    static char* remaining = NULL;
    t_string line;
    ssize_t bytes_read;

    if (BUFFER_SIZE <= 0 || fd < 0 || fd >= MAX_FD)
        return (NULL);
    line = string_init();
    if (!remaining)
    {
        remaining = malloc(1 + BUFFER_SIZE);
        *remaining = '\0';
    }
    // if remaining contains a newline, after this, line will contain a newline
    // else, remaining will be an empty string
    if (*remaining)
        move_until_newline(&line, remaining);

    bytes_read = ARBITRARY_POSITIVE_VALUE;
    while (bytes_read > 0 && !ft_strchr(line.data, '\n'))
        bytes_read = load_buffer(line, remaining, fd);

    if (remaining[0] == '\0' && bytes_read == 0)
    {
        free(remaining);
        return NULL;
    }
    if (line.data[0] == '\0')
    {
        free(line.data);
        return NULL;
    }
    return line.data;
}

ssize_t move_until_newline(t_string* str_ref, char* src)
{
    char* newline_position = ft_strchr(src, '\n');
    size_t newline_index;

    if (newline_position == NULL)
    {
        string_append(str_ref, src);
        return 0;
    }
    else
    {
        newline_index = newline_position - src;
        string_append_substring(str_ref, src, newline_index + 1);
        ft_strcpy(src, newline_position + 1);
        return 0;
    }
}

ssize_t load_buffer(t_string line, char* remaining, int fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
    ft_strlcpy(remaining, buffer, 1 + BUFFER_SIZE);
    move_until_newline(&line, remaining);
    return bytes_read;
}
