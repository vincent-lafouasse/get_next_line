/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlafouas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:41:06 by vlafouas          #+#    #+#             */
/*   Updated: 2023/12/24 12:15:52 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

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
