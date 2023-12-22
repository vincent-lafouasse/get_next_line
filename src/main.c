/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/22 16:33:11 by vlafouas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

size_t	ft_strlen(const char *s);
char	*ft_strjoin(const char *s1, const char *s2);
char 	*ft_strdup(const char* s);
char	*ft_strnchr(const char *s, char c, size_t n);
void	flush_buffer(char *buffer, char **out, size_t buffer_size);

char	*gnl(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*out;

	out = ft_strdup("");
	return (out);
}

int	main(void)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	size_t	i;

	fd = open(PATH, O_RDONLY);
	bzero(buffer, BUFFER_SIZE);
	i = 0;
	while (read(fd, buffer + i, 1) > 0)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			break ;
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
			break ;
		}
		i++;
	}
	printf("second line\n");
	printf("%s\n", buffer);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*out;
	const char	*str_begin;

	out = malloc(1 + ft_strlen(s1) + ft_strlen(s2));
	str_begin = out;
	while (*s1)
		*out++ = *s1++;
	while (*s2)
		*out++ = *s2++;
	*out = 0;
	return ((char *)str_begin);
}

char 	*ft_strdup(const char* s)
{
	char* out = malloc(1 + ft_strlen(s));
	const char* head = out;

	while (*s)
		*out++ = *s++;
	*out = '\0';
	return (char*)head;
}
char	*ft_strnchr(const char *s, char c, size_t n)
{
	size_t i = 0;

	while (i < n && i <= ft_strlen(s))
	{
		if (s[i] == c)
			return (char*)s + i;
	}
	return NULL;
}

