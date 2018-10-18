#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
        int val;
        struct node *next;
};

typedef struct node list_t;

void push(int val, list_t **l);

int pop(list_t **l);

void *free_list(list_t **l);

void free_node(struct node *n);

void print_list(list_t **l);

#endif
