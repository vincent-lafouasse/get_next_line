/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/23 22:48:16 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

static void log_buffer(const char* buffer, size_t buffer_size)
{
	printf("new buffer:\n\t");

	for (size_t i = 0; i < buffer_size; i++)
	{
		if (buffer[i] == '\n')
			printf("$");
		else
			printf("%c", buffer[i]);
	}
	printf("\n");
}

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
	char		*line;

	line = ft_strdup("");
	while (ft_strnchr(buffer, '\n', BUFFER_SIZE) == NULL)
	{
		flush_buffer(buffer, &line);
		bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		log_buffer(buffer, BUFFER_SIZE);
		if (bytes_read < BUFFER_SIZE)
			break;
	}

	char* newline_position = ft_strnchr(buffer, '\n', BUFFER_SIZE);

	return (line);
}

int	main(void)
{
	int		fd;
	char* line;

	fd = open(PATH, O_RDONLY);

	line = gnl(fd);
	printf("%s", line);
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
