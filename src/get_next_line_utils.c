/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:53:56 by poss              #+#    #+#             */
/*   Updated: 2024/04/05 21:04:35 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

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

static size_t min(size_t a, size_t b);

char* ft_substr(char const* s, unsigned int start, size_t len)
{
    char* out;

    if (start >= ft_strlen(s))
        return (ft_strdup(""));
    len = min(len, ft_strlen(s + start));
    out = malloc(1 + len);
    if (!out)
        return (NULL);
    ft_strlcpy(out, s + start, 1 + len);
    return (out);
}

static size_t min(size_t a, size_t b)
{
    if (a < b)
        return (a);
    return (b);
}
