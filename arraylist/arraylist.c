#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

struct arraylist new_list(size_t capacity)
{
        struct arraylist al;
        al.capacity = capacity;
        al.arr = malloc(sizeof(void *) * (al.capacity));
        al.size = 0;
        return al;
}

void add(struct arraylist *al, void *x)
{
        if (al->size == al->capacity - 1) {
                al->capacity *= 2;
                al->arr = realloc(al->arr, sizeof(void *) * (al->capacity));
        }
        al->arr[(al->size)++] = x;
}

// FIXME: run valgrind and diagnose
void *remove_by_index(struct arraylist *l, int index)
{
        void *ret = l->arr[index];
        size_t ncopy = sizeof(void *) * (l->capacity - (index + 1));
        memmove(l->arr + index, l->arr + index + 1, ncopy);
        l->size--;
        return ret;
}

void free_list(struct arraylist *l)
{
        free(l->arr);
}

void print_list(struct arraylist *l)
{
        printf("print_list: not implemented\n");
}
