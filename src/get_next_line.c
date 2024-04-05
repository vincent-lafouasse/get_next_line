/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2024/04/05 20:36:20 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

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

#define INITIAL_CAPACITY 128
#define GROWING_FACTOR 1.3

char* ft_strcpy(char* dest, const char* src)
{
    const char* start = src;
    while (*src)
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return (char*)start;
}

typedef struct
{
    char* data;
    size_t len;
    size_t capacity;
} t_string;

t_string init_string(void)
{
    t_string out;
    out.data = malloc(INITIAL_CAPACITY);
    out.data[0] = '\0';
    out.len = 0;
    out.capacity = INITIAL_CAPACITY;
    return out;
}

void realloc_string(t_string* str_ref)
{
    size_t new_capacity = GROWING_FACTOR * (double)(str_ref->capacity);
    if (new_capacity < str_ref->capacity)
        return;
    char* new_data = malloc(new_capacity);
    ft_memcpy(new_data, str_ref->data, str_ref->capacity);
    str_ref->data = new_data;
    str_ref->capacity = new_capacity;
}

bool str_contains(t_string str, int c)
{
    return ft_strchr(str.data, c);
}

void append_substring(t_string* str_ref, const char* s, size_t len);

void append_string(t_string* str_ref, const char* s)
{
    append_substring(str_ref, s, ft_strlen(s));
}

static size_t min_size(size_t a, size_t b)
{
    if (a < b)
        return a;
    else
        return b;
}
void append_substring(t_string* str_ref, const char* s, size_t len)
{
    size_t n_bytes = min_size(len, ft_strlen(s));
    size_t input_len = ft_strlen(str_ref->data);

    while (str_ref->capacity < n_bytes + input_len)
        realloc_string(str_ref);
    ft_memcpy(str_ref->data + input_len , s, n_bytes);
    str_ref->data[input_len + n_bytes] = '\0';
}

ssize_t move_until_newline(t_string* str_ref, char* src)
{
    char* newline_position = ft_strchr(src, '\n');
    size_t newline_index;

    if (newline_position == 0)
    {
        append_string(str_ref, src);
        return 0;
    }
    else
    {
        newline_index = newline_position - src;
        append_substring(str_ref, src, newline_index + 1);
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

char* get_next_line(int fd)
{
    static char* remaining = NULL;
    t_string line = init_string();
    ssize_t bytes_read;

    if (!remaining)
    {
        remaining = malloc(1 + BUFFER_SIZE);
        *remaining = '\0';
    }
    if (*remaining)
        move_until_newline(&line, remaining);

    bytes_read = ARBITRARY_POSITIVE_VALUE;
    while (bytes_read && !ft_strchr(line.data, '\n'))
        bytes_read = load_buffer(line, remaining, fd);

    if (line.data[0] == '\0')
    {
        free(line.data);
        line.data = NULL;
    }
    return line.data;
}
