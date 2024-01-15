/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 00:12:52 by poss              #+#    #+#             */
/*   Updated: 2024/01/16 00:21:24 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
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

bool	char_queue_push_back(t_char_queue **q_ptr, char c)
{
	t_char_queue	*new;
	t_char_queue	*current;

	if (!q_ptr)
		return (false);
	new = char_queue_new(c);
	if (!new)
		return (false);
	if (*q_ptr == NULL)
	{
		*q_ptr = new;
		return (true);
	}
	current = *q_ptr;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
	return (true);
}

char	char_queue_pop_front(t_char_queue **q_ptr)
{
	t_char_queue	*temp;
	char			out;

	if (!q_ptr || !*q_ptr)
		return (-1);
	out = (*q_ptr)->c;
	temp = (*q_ptr)->next;
	free(*q_ptr);
	*q_ptr = temp;
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
