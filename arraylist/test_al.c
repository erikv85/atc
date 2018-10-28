#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

typedef struct arraylist list_t;

void test1(int);

int main(int argc, char **argv)
{
        int default_size = 4;
        test1(default_size);
        return 0;
}

void test1(int default_size)
{
        list_t *l = new_list(default_size);
        int i;
        for (i = 0; i <= default_size; i++) {
                printf("adding %d\n", i+1);
                add(l, i + 1);
        }
        printf("capacity, size = %ld, %d\n", l->capacity, l->size);

        print_list(l);
        for (i = 0; i <= default_size; i++) {
                printf("%d ", l->arr[i]);
        }
        printf("\n");
        printf("removed elem: %d\n", remove_by_index(l, 2));
        print_list(l);
        for (i = 0; i <= default_size; i++) {
                printf("%d ", l->arr[i]);
        }
        printf("\n");
        free_list(l);
}
