/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 11:01:37 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

void	log_cqueue(t_cqueue *q)
{
	while (q)
	{
		printf("%c", q->c);
		q = q->next;
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
	cqueue_push(&q, ' ');
	cqueue_push(&q, 'l');
	cqueue_push(&q, 'o');
	cqueue_push(&q, 'l');
	log_cqueue(q);
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

void	cqueue_pop(t_cqueue **q)
{
	t_cqueue	*temp;

	if (!q || !*q)
		return ;
	temp = (*q)->next;
}
