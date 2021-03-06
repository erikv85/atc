#include <stdio.h>
#include <stdlib.h> /* malloc, free */

#include "linked_list.h"

char *int_to_string(void *i)
{
        char *str = malloc(20 * sizeof(char));
        sprintf(str, "%d", *(int *)i);
        return str;
}

void test1();

void test2();

int main(int argc, char **argv)
{
        test2();

        return 0;
}

void test1()
{
        list_t **l = malloc(sizeof(struct node *));
        int x[] = { 2, 3, 5, 7, 11, 13 };
        print_list(l, int_to_string);
        push(l, x);
        print_list(l, int_to_string);
        push(l, x+1);
        print_list(l, int_to_string);
        push(l, x+2);
        print_list(l, int_to_string);
        push(l, x+3);
        print_list(l, int_to_string);
        push(l, x+4);
        print_list(l, int_to_string);
        push(l, x+5);
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
        print_list(l, int_to_string);
        l = free_list(l);
        printf("l addr: %p\n", l);
        print_list(l, int_to_string);
}

void test2()
{
        list_t **l2 = malloc(sizeof(struct node *));
        int y[] = { 2, 3, 5, 7, 11, 13 };
        print_list(l2, int_to_string);
        add(l2, y);
        print_list(l2, int_to_string);
        add(l2, y+1);
        print_list(l2, int_to_string);
        add(l2, y+2);
        print_list(l2, int_to_string);
        add(l2, y+3);
        print_list(l2, int_to_string);
        add(l2, y+4);
        print_list(l2, int_to_string);
        add(l2, y+5);
        print_list(l2, int_to_string);
        printf("%d\n", *(int *)pop(l2));
        print_list(l2, int_to_string);

        printf("0th item: %d\n", *(int *)get(l2, 0));
        printf("1st item: %d\n", *(int *)get(l2, 1));
        printf("2nd item: %d\n", *(int *)get(l2, 2));
        printf("last item: %d\n", *(int *)get(l2, size(l2) - 1));
        printf("removed %d\n", *(int *)remove_by_index(l2, 0));
        printf("size: %d\n", size(l2));
        printf("removed %d\n", *(int *)remove_by_index(l2, size(l2) - 1));
        print_list(l2, int_to_string);
        l2 = free_list(l2);
        printf("l2 addr: %p\n", l2);
        print_list(l2, int_to_string);
}
