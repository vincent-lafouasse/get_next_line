/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:00:32 by poss              #+#    #+#             */
/*   Updated: 2023/12/24 13:16:46 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

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
	char		out;

	if (!q || !*q)
		return (-1);
	out = (*q)->c;
	temp = (*q)->next;
	free(*q);
	*q = temp;
	return (out);
}

bool	queue_contains(const t_cqueue *q, char c)
{
	while (q)
	{
		if (q->c == c)
			return (true);
		q = q->next;
	}
	return (false);
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
