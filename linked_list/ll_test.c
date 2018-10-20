#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

int main(int argc, char **argv)
{
        list_t **l = malloc(sizeof(struct node *));
        print_list(l);
        push(2, l);
        print_list(l);
        push(3, l);
        print_list(l);
        push(5, l);
        print_list(l);
        push(7, l);
        print_list(l);
        push(11, l);
        print_list(l);
        push(13, l);
        print_list(l);
        printf("%d\n", pop(l));
        print_list(l);

        printf("0th item: %d\n", get(l, 0));
        printf("1st item: %d\n", get(l, 1));
        printf("2nd item: %d\n", get(l, 2));
        printf("last item: %d\n", get(l, size(l) - 1));
        printf("removed %d\n", remove_item(l, 0));
        printf("size: %d\n", size(l));
        printf("removed %d\n", remove_item(l, size(l) - 1));
        print_list(l);
        l = free_list(l);
        printf("l addr: %p\n", l);
        print_list(l);

        return 0;
}
