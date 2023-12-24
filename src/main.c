/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 11:41:33 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

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

static void log_line(const char* line)
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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

char	*gnl(int fd)
{
	char	*a;

	a = malloc(1 + fd);
	return (a);
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

size_t	line_length(const t_cqueue *q)
{
	size_t	len;
	char	last_char;

	len = 0;
	last_char = 0;
	while (q)
	{
		len++;
		last_char = q->c;
		if (q->c == '\n')
			break ;
		q = q->next;
	}
	if (last_char != '\n')
		return (len + 1);
	return (len);
}

char *move_line_from_queue(t_cqueue **q)
{
	char* line = malloc(1 + line_length(*q));
	const char* line_start = line;
	char last_char = 0;

	while (*q)
	{
		*line = cqueue_pop(q);
		last_char = *line;
		line++;
		if (last_char == '\n')
			break;
	}
	if (last_char != '\n')
		*line++ = '\n';
	*line = '\0';
	return (char*)line_start;
}

t_cqueue	*cqueue_new(char c)
{
	t_cqueue	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void	cqueue_push(t_cqueue **q, char c)
{
	t_cqueue	*new;
	t_cqueue	*current;

	new = cqueue_new(c);
	if (!new || !q)
		return ;
	if (*q == NULL)
	{
		*q = new;
		return ;
	}
	current = *q;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

char	cqueue_pop(t_cqueue **q)
{
	t_cqueue	*temp;
	char out;

	if (!q || !*q)
		return -1;
	out = (*q)->c;
	temp = (*q)->next;
	free(*q);
	*q = temp;
	return out;
}
