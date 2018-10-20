/**
 * Program shows how to use a generic linked list together with the
 * list value-type's specific "to_string" method.
 */

#include <stdio.h>
#include <stdlib.h>

struct node { void *val; struct node *next; };

void *peek(struct node **list) { return (*list)->val; }

char *list_to_string(struct node **list, char *(*to_string)(void *)) {
       return to_string(peek(list));
}

struct point { int x,y; };

char *point_to_string(void *val) {
        struct point pt = *(struct point *)val;
        char *str = malloc(10);
        sprintf(str, "(%d, %d)", pt.x, pt.y);
        return str;
}

void main() {
        struct point pt = { 2, 3 };
        struct node **l = malloc(sizeof(struct node *));
        *l = malloc(sizeof(struct node));
        (*l)->val = (void *)(&pt);
        (*l)->next = NULL;
        char *foofoo = list_to_string(l, point_to_string);
        printf("%s\n", foofoo);
}
