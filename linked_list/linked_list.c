#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

void push(int val, list_t **l)
{
        struct node *newnode = malloc(sizeof(struct node));
        newnode->val = val;
        newnode->next = *l;
        *l = newnode;
}

int pop(list_t **l)
{
	struct node *next = (*l)->next;
        int ret = (*l)->val;
        free(*l);
        *l = next;
        return ret;
}

void *free_list(list_t **l)
{
        if (!l) {
                ;
        } else {
                if (*l)
                        free_node(*l);
                free(l);
        }
        return NULL;
}

void free_node(struct node *n)
{
        if (n->next)
                free_node(n->next);
        free(n);
}

void print_list(list_t **l)
{
        printf("[");
        if (!l || !*l) {
                ;
        } else {
                printf("%d", (*l)->val);
                struct node *tmp = (*l)->next;
                while (tmp) {
                        printf(", %d", tmp->val);
                        tmp = tmp->next;
                }
        }
        printf("]\n");
}
