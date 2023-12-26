/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:32:34 by poss              #+#    #+#             */
/*   Updated: 2023/12/26 15:27:30 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <sys/types.h>

typedef struct s_char_queue
{
	char			c;
	struct s_char_queue	*next;
}					t_char_queue;

char				*get_next_line(int fd);

void				char_queue_push(t_char_queue **q, char c);
t_char_queue			*char_queue_new(char c);
char				char_queue_pop(t_char_queue **q);
size_t				line_length(const t_char_queue *q);

char				*move_line_from_queue(t_char_queue **q);
ssize_t				load_queue(t_char_queue **q, int fd, size_t buffer_size);
bool				queue_contains(const t_char_queue *q, char c);

#endif
