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
        printf("%d\n", pop(l));
        print_list(l);
        l = free_list(l);
        print_list(l);
        printf("l addr: %p\n", l);

	return 0;
}
