/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: poss <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 12:32:34 by poss              #+#    #+#             */
/*   Updated: 2023/12/24 12:32:35 by poss             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

typedef struct s_cqueue
{
	char			c;
	struct s_cqueue	*next;
}					t_cqueue;

char				*get_next_line(int fd);

void				cqueue_push(t_cqueue **q, char c);
t_cqueue			*cqueue_new(char c);
char				cqueue_pop(t_cqueue **q);
size_t				line_length(const t_cqueue *q);

char				*move_line_from_queue(t_cqueue **q);
ssize_t				load_queue(t_cqueue **q, int fd, size_t buffer_size);
bool				queue_contains(const t_cqueue *q, char c);

void				log_cqueue(t_cqueue *q);
void				log_line(const char *line);

#endif
