#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

void push(list_t **l, void *val)
{
        struct node *newnode = malloc(sizeof(struct node));
        newnode->val = val;
        newnode->next = *l;
        *l = newnode;
}

void *get(list_t **l, int index)
{
        int curr = 0;
        struct node *tmp = *l;
        while (curr != index) {
                curr++;
                tmp = tmp->next;
        }
        return tmp->val;
}

void *remove_by_index(list_t **l, int index)
{
        struct node *tmp = *l;
        void *val;
        if (index == 0) {
                *l = (*l)->next;
                val = tmp->val;
                free(tmp);
        } else {
                int curr = 0;
                while (curr != index - 1) {
                        tmp = tmp->next;
                        curr++;
                }
                val = tmp->next->val;
                struct node *newnext = tmp->next->next;
                free(tmp->next);
                tmp->next = newnext;
        }
        return val;
}

void *pop(list_t **l)
{
        struct node *next = (*l)->next;
        void *ret = (*l)->val;
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

void print_list(list_t **l, char *(*to_string)(void *))
{
        printf("[");
        if (!l || !*l) {
                ;
        } else {
                char *str = to_string((*l)->val);
                printf("%s", str);
                free(str);
                struct node *tmp = (*l)->next;
                while (tmp) {
                        str = to_string(tmp->val);
                        printf(", %s", str);
                        free(str);
                        tmp = tmp->next;
                }
        }
        printf("]\n");
}

int size(list_t **l)
{
        int size = 0;
        struct node *tmp = *l;
        while (tmp) {
                size++;
                tmp = tmp->next;
        }
        return size;
}
