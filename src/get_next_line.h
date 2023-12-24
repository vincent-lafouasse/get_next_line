#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>

typedef struct s_cqueue
{
	char			c;
	struct s_cqueue	*next;
}					t_cqueue;

char				*cqueue_to_str(const t_cqueue *q);
void				cqueue_push(t_cqueue **q, char c);
t_cqueue			*cqueue_new(char c);
char				cqueue_pop(t_cqueue **q);
size_t				line_length(const t_cqueue *q);
char				*move_line_from_queue(t_cqueue **q);
ssize_t				load_queue(t_cqueue **q, int fd, size_t buffer_size);

#endif
