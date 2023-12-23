/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/23 18:54:21 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
char	*ft_strnchr(const char *s, char c, size_t n);

void	flush_buffer(char *buffer, char **out)
{
	char	*tmp;

	tmp = ft_strjoin(*out, buffer);
	free(*out);
	*out = tmp;
}

char	*gnl(int fd)
{
	static char buffer[BUFFER_SIZE] = {0};
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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*out;

	out = malloc(1 + strlen(s1) + strlen(s2));
	memcpy(out, s1, strlen(s1));
	memcpy(out + strlen(s1), s2, 1 + strlen(s2));
	return out;
}

char	*ft_strdup(const char *s)
{
	char		*out;

	out = malloc(1 + strlen(s));
	memcpy(out, s, 1 + strlen(s));
	return out;
}

char	*ft_strnchr(const char *s, char c, size_t n)
{
	return memchr(s, c, strnlen(s, n));
}
