/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 12:01:06 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

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

char	*move_line_from_queue(t_cqueue **q)
{
	char		*line;
	const char	*line_start;
	char		last_char;

	line = malloc(1 + line_length(*q));
	line_start = line;
	last_char = 0;
	while (*q)
	{
		*line = cqueue_pop(q);
		last_char = *line;
		line++;
		if (last_char == '\n')
			break ;
	}
	if (last_char != '\n')
		*line++ = '\n';
	*line = '\0';
	return ((char *)line_start);
}
