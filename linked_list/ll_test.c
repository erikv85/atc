#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

char *int_to_string(void *i)
{
        char *str = malloc(20 * sizeof(char));
        sprintf(str, "%d", *(int *)i);
        return str;
}

int main(int argc, char **argv)
{
        list_t **l = malloc(sizeof(struct node *));
        int x[] = { 2, 3, 5, 7, 11, 13 };
        print_list(l, int_to_string);
        push(x, l);
        print_list(l, int_to_string);
        push(x+1, l);
        print_list(l, int_to_string);
        push(x+2, l);
        print_list(l, int_to_string);
        push(x+3, l);
        print_list(l, int_to_string);
        push(x+4, l);
        print_list(l, int_to_string);
        push(x+5, l);
        print_list(l, int_to_string);
        printf("%d\n", *(int *)pop(l));
        print_list(l, int_to_string);

        printf("0th item: %d\n", *(int *)get(l, 0));
        printf("1st item: %d\n", *(int *)get(l, 1));
        printf("2nd item: %d\n", *(int *)get(l, 2));
        printf("last item: %d\n", *(int *)get(l, size(l) - 1));
        printf("removed %d\n", *(int *)remove_by_index(l, 0));
        printf("size: %d\n", size(l));
        printf("removed %d\n", *(int *)remove_by_index(l, size(l) - 1));
        //printf("removed %d\n", remove_by_value(l, 5));
        print_list(l, int_to_string);
        l = free_list(l);
        printf("l addr: %p\n", l);
        print_list(l, int_to_string);

        return 0;
}
