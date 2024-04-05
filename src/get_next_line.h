/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 17:52:32 by poss              #+#    #+#             */
/*   Updated: 2024/04/05 19:15:46 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stddef.h>

char* get_next_line(int fd);

char* ft_strchr(const char* s, int c);
size_t ft_strlen(const char* s);
char* ft_strjoin(char const* s1, char const* s2);
char* ft_substr(char const* s, unsigned int start, size_t len);
char* ft_strdup(const char* s);
void* ft_memcpy(void* dest, const void* src, size_t n);
size_t ft_strlcpy(char* dst, const char* src, size_t buffer_size);
char* ft_substr(char const* s, unsigned int start, size_t len);

#endif
