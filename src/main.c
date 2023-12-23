/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/23 23:19:28 by poss             ###   ########.fr       */
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

void rotate(char* array, size_t shift, size_t array_size)
{
    size_t p = 1;
    while (p <= shift) {
        int last = array[0];
        for (size_t i = 0; i < array_size - 1; i++) {
            array[i] = array[i + 1];
        }
        array[array_size - 1] = last;
        p++;
    }
}

static void log_buffer(const char* buffer, size_t buffer_size)
{
	printf("buffer:\t");

	for (size_t i = 0; i < buffer_size && buffer[i]; i++)
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
	printf("here\n");

	char* newline_position = ft_strnchr(buffer, '\n', BUFFER_SIZE);

	*newline_position = 0;
	flush_buffer(buffer, &line);
	flush_buffer("\n", &line);

	bzero(buffer, (newline_position - buffer));
	rotate(buffer, 1 + (newline_position - buffer), BUFFER_SIZE);

	return (line);
}

int	main(void)
{
	int		fd;
	char* line;

	fd = open(PATH, O_RDONLY);

	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*out;

	printf("joining \"%s\" and \"%s\"\n", s1, s2);
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
