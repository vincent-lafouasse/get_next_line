/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:53:56 by poss              #+#    #+#             */
/*   Updated: 2024/04/05 21:10:30 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

static size_t min_size(size_t a, size_t b);

// t_string operations

#define INITIAL_CAPACITY 128
#define GROWING_FACTOR 1.3

t_string init_string(void)
{
    t_string out;
    out.data = malloc(INITIAL_CAPACITY);
    out.data[0] = '\0';
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

void append_substring(t_string* str_ref, const char* s, size_t len)
{
    size_t n_bytes = min_size(len, ft_strlen(s));
    size_t input_len = ft_strlen(str_ref->data);

    while (str_ref->capacity < n_bytes + input_len)
        realloc_string(str_ref);
    ft_memcpy(str_ref->data + input_len, s, n_bytes);
    str_ref->data[input_len + n_bytes] = '\0';
}

void append_string(t_string* str_ref, const char* s)
{
    append_substring(str_ref, s, ft_strlen(s));
}

// libft
typedef unsigned char t_byte;

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

void* ft_memcpy(void* dest, const void* src, size_t n)
{
    t_byte* dest_bytes;
    t_byte* src_bytes;

    dest_bytes = (t_byte*)dest;
    src_bytes = (t_byte*)src;
    while (n)
    {
        *dest_bytes = *src_bytes;
        n--;
        dest_bytes++;
        src_bytes++;
    }
    return (dest);
}

char* ft_strjoin(char const* s1, char const* s2)
{
    size_t len1;
    size_t len2;
    char* out;

    if (!s1 || !s2)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    out = malloc(len1 + len2 + 1);
    if (!out)
        return (NULL);
    ft_memcpy(out, s1, len1);
    ft_memcpy(out + len1, s2, len2);
    out[len1 + len2] = '\0';
    return (out);
}

char* ft_strdup(const char* s)
{
    char* out;
    size_t len;

    len = ft_strlen(s);
    out = malloc(1 + len);
    if (!out)
        return (NULL);
    ft_memcpy(out, s, 1 + len);
    return (out);
}

size_t ft_strlen(const char* s)
{
    size_t len;

    len = 0;
    while (*s)
    {
        s++;
        len++;
    }
    return (len);
}

char* ft_strchr(const char* s, int c)
{
    while (1)
    {
        if (*s == (unsigned char)c)
        {
            return ((char*)s);
        }
        if (*s == '\0')
        {
            return (NULL);
        }
        s++;
    }
}

size_t ft_strlcpy(char* dst, const char* src, size_t buffer_size)
{
    size_t i;

    if (buffer_size == 0)
    {
        return (ft_strlen(src));
    }
    i = 0;
    while (src[i] && i < buffer_size - 1)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (ft_strlen(src));
}

char* ft_substr(char const* s, unsigned int start, size_t len)
{
    char* out;

    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    len = min_size(len, ft_strlen(s + start));
    out = malloc(1 + len);
    if (!out)
        return (NULL);
    ft_strlcpy(out, s + start, 1 + len);
    return (out);
}

static size_t min_size(size_t a, size_t b)
{
    if (a < b)
        return a;
    else
        return b;
}
