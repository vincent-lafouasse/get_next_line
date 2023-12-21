#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

typedef struct s_char_node {
	char c;
	struct s_char_node* next;
} t_char_node;

typedef struct s_char_list {
	t_char_node* head;
} t_char_list;

char* get_next_line(int fd);

char* char_list_to_str(const s_char_list lst);
void char_list_push(s_char_list* lst, char c);

#endif
