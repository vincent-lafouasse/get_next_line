/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/22 14:28:55 by vlafouas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

size_t ft_strlen(const char* s);
char* ft_strjoin(const char* s1, const char* s2);
char* ft_strnchr(const char* s, char c, size_t n);
void  flush_buffer(char* buffer, char** out, size_t buffer_size);

char* gnl(int fd)
{
	static char buffer[BUFFER_SIZE];
	char* out = malloc(1);
	return out;
}

int main(void)
{
	int fd = open(PATH, O_RDONLY);

	char buffer[BUFFER_SIZE];
	bzero(buffer, BUFFER_SIZE);

	size_t i = 0;

	while (read(fd, buffer + i, 1) > 0)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	printf("first line\n");
	printf("%s\n", buffer);

	bzero(buffer, BUFFER_SIZE);
	i = 0;
	while (read(fd, buffer + i, 1) > 0)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			break;
		}
		i++;
	}
	printf("second line\n");
	printf("%s\n", buffer);

}

size_t ft_strlen(const char* s)
{
	size_t len = 0;

	while (*s)
	{
		len++;
		s++;
	}
	return len;
}

char* ft_strjoin(const char* s1, const char* s2)
{
	char* out = malloc(1 + ft_strlen(s1) + ft_strlen(s2));
	const char* str_begin = out;
	while (*s1)
		*out++ = *s1++;
	while (*s2)
		*out++ = *s2++;
	*out = 0;

	return (char*)str_begin;
}
