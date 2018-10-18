#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

/* Assume list root is not null */
void push(void *val, node_t **root)
{
        node_t *newnode = malloc(sizeof(node_t));
        newnode->val = val;
        newnode->next = *root;
        *root = newnode;
}

/* Remove first item. */
void *pop(node_t **root)
{
        if (!*root)
                return NULL;

	node_t *next = (*root)->next;
        void *ret = (*root)->val;
        free(*root);
        *root = next;

        return ret;
}

void free_list(node_t *root)
{
        node_t *tmp;
        while (root) {
                tmp = root;
                root = root->next;
                free(tmp);
        }
}
