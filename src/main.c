/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:11:45 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 10:42:04 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH "./aux/short.txt"

void log_clst(t_clist* lst)
{
	while (lst)
	{
		printf("%c", lst->c);
		lst = lst->next;
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
	/*
	int		fd;
	char	*line;

	fd = open(PATH, O_RDONLY);
	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	*/
	t_clist* lst = NULL;
	clist_push_back(&lst, '4');
	clist_push_back(&lst, '2');
	clist_push_back(&lst, '0');
	log_clst(lst);
}

t_clist	*clist_new(char c)
{
	t_clist* new = malloc(sizeof(*new));
	
	new->c = c;
	new->next = NULL;

	return new;
}

void	clist_push_back(t_clist **lst, char c)
{
	t_clist* new = clist_new(c);

	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	while ((*lst)->next)
	{
		*lst = (*lst)->next;
	}
	(*lst)->next = new;
}
