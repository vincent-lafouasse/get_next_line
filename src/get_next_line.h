/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:52:32 by poss              #+#    #+#             */
/*   Updated: 2024/04/09 16:11:34 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdbool.h>
#include <stddef.h>

char* get_next_line(int fd);

// t_string type
typedef struct
{
    char* data;
    size_t capacity;
} t_string;

t_string init_string(void);
t_string init_string_with_capacity(size_t capacity);
t_string init_string_from_cstr(const char* s);
void realloc_string(t_string* str_ref);
bool str_contains(t_string str, int c);

void append_string(t_string* str_ref, const char* s);
void append_substring(t_string* str_ref, const char* s, size_t len);

// libft functions
char* ft_strcpy(char* dest, const char* src);
char* ft_strchr(const char* s, int c);
size_t ft_strlen(const char* s);
char* ft_strjoin(char const* s1, char const* s2);
char* ft_substr(char const* s, unsigned int start, size_t len);
char* ft_strdup(const char* s);
void* ft_memcpy(void* dest, const void* src, size_t n);
size_t ft_strlcpy(char* dst, const char* src, size_t buffer_size);
char* ft_substr(char const* s, unsigned int start, size_t len);

#endif
