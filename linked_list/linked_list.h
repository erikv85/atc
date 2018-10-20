#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
        void *val;
        struct node *next;
};

typedef struct node list_t;

void push(void *val, list_t **l);

void *pop(list_t **l);

void *remove_by_index(list_t **l, int index);

int remove_by_value(list_t **l, int val);

void *get(list_t **l, int index);

void *free_list(list_t **l);

void free_node(struct node *n);

void print_list(list_t **l, char *(*to_string)(void *));

int size(list_t **l);

#endif
