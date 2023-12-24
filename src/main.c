/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 12:12:02 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

static void	log_cqueue(t_cqueue *q);
static void	log_line(const char *line);

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

ssize_t	load_queue(t_cqueue **q, int fd, size_t buffer_size)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	ssize_t	i;

	bytes_read = read(fd, buffer, buffer_size);
	i = 0;
	if (bytes_read <= 0)
	{
		return (0);
	}
	while (i < bytes_read)
	{
		cqueue_push(q, buffer[i]);
		i++;
	}
	return (bytes_read);
}

int	main(void)
{
	int			fd;
	char		*line;
	t_cqueue	*q;

	(void)fd;
	/*
	fd = open(PATH, O_RDONLY);
	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	*/
	q = NULL;
	cqueue_push(&q, '4');
	cqueue_push(&q, '2');
	cqueue_push(&q, '0');
	cqueue_push(&q, '\n');
	cqueue_push(&q, 'h');
	cqueue_push(&q, 'a');
	cqueue_push(&q, 'h');
	cqueue_push(&q, 'a');
	log_cqueue(q);
	printf("line length\t%zu\n", line_length(q));
	line = move_line_from_queue(&q);
	printf("line contains\n");
	log_line(line);
	printf("queue contains\n");
	log_cqueue(q);
	printf("\nline length\t%zu\n", line_length(q));
	line = move_line_from_queue(&q);
	printf("line contains\n");
	log_line(line);
	printf("queue contains\n");
	log_cqueue(q);
}

static void	log_cqueue(t_cqueue *q)
{
	while (q)
	{
		if (q->c == '\n')
			printf("$");
		else
			printf("%c", q->c);
		q = q->next;
	}
	printf("\n");
}

static void	log_line(const char *line)
{
	while (*line)
	{
		if (*line == '\n')
			printf("$");
		else
			printf("%c", *line);
		line++;
	}
	printf("\n");
}
