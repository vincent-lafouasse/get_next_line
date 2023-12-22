/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/22 17:05:35 by vlafouas         ###   ########.fr       */
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
char	*ft_strdup(const char *s);
char	*ft_strnchr(const char *s, char c, size_t n);
void* 	ft_memcpy(void* dst, const void* src, const size_t sz)
{
	size_t i = 0;
	unsigned char* dst__ = dst;
	const unsigned char* src__ = src;

	while (i < sz)
	{
		dst__[i] = src__[i];
	}
	return dst;
}

void	flush_buffer(char *buffer, char **out)
{
	char	*tmp;

	tmp = ft_strjoin(*out, buffer);
	free(*out);
	*out = tmp;
}

char	*gnl(int fd)
{
	static char	buffer[BUFFER_SIZE];
	size_t		bytes_read;
	char		*out;

	out = ft_strdup("");
	while (ft_strnchr(buffer, '\n', BUFFER_SIZE) == NULL)
	{
		flush_buffer(buffer, &out);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
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

	out = malloc(1 + ft_strlen(s1) + ft_strlen(s2));
	ft_memcpy(out, s1, ft_strlen(s1));
	ft_memcpy(out + ft_strlen(s1), s2, 1 + ft_strlen(s2));
	return out;
}

char	*ft_strdup(const char *s)
{
	char		*out;

	out = malloc(1 + ft_strlen(s));
	ft_memcpy(out, s, 1 + ft_strlen(s));
	return out;
}

char	*ft_strnchr(const char *s, char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && i <= ft_strlen(s))
	{
		if (s[i] == c)
			return ((char *)s + i);
	}
	return (NULL);
}
