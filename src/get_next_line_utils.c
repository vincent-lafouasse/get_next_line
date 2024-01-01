/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:00:32 by poss              #+#    #+#             */
/*   Updated: 2024/01/01 13:24:26 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_char_queue	*char_queue_new(char c)
{
	t_char_queue	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->c = c;
	new->next = NULL;
	return (new);
}

void	char_queue_push_back(t_char_queue **q, char c)
{
	t_char_queue	*new;
	t_char_queue	*current;

	new = char_queue_new(c);
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

char	char_queue_pop_front(t_char_queue **q)
{
	t_char_queue	*temp;
	char			out;

	if (!q || !*q)
		return (-1);
	out = (*q)->c;
	temp = (*q)->next;
	free(*q);
	*q = temp;
	return (out);
}

bool	char_queue_contains(const t_char_queue *q, char c)
{
	while (q)
	{
		if (q->c == c)
			return (true);
		q = q->next;
	}
	return (false);
}

size_t	line_length(const t_char_queue *q)
{
	size_t	len;

	len = 0;
	while (q)
	{
		len++;
		if (q->c == '\n')
			break ;
		q = q->next;
	}
	return (len);
}
