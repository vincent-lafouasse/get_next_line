#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct s_cqueue
{
	char			c;
	struct s_cqueue	*next;
}					t_cqueue;

char				*cqueue_to_str(const t_cqueue *q);
void				cqueue_push(t_cqueue **q, char c);
t_cqueue			*cqueue_new(char c);
void				cqueue_pop(t_cqueue **q);
size_t				line_length(const t_cqueue *q);

#endif
