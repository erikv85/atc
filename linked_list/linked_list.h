#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node {
  void *val;
  struct node *next;
} node_t;

void push(void *val, node_t **root);

void *pop(node_t **root);

void free_list(node_t *root);

#endif
