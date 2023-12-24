#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>

typedef struct s_clist
{
	char			c;
	struct s_clist	*next;
}					t_clist;

char				*clist_to_str(const t_clist *lst);
void				clist_push_back(t_clist **lst, char c);
t_clist				*clist_new(char c);

#endif
