#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arraylist.h"

struct arraylist *new_list(size_t capacity)
{
    struct arraylist *al = malloc(sizeof(struct arraylist));
    al->capacity = capacity;
    al->arr = malloc(sizeof(int) * (al->capacity));
    al->size = 0;
    return al;
}

void add(struct arraylist *al, int x)
{
    if (al->size == al->capacity - 1) {
        al->capacity *= 2;
        al->arr = realloc(al->arr, sizeof(int) * (al->capacity));
    }
    al->arr[(al->size)++] = x;
}

// FIXME: run valgrind and diagnose
int remove_by_index(struct arraylist *l, int index)
{
    int ret = l->arr[index];
    size_t ncopy = sizeof(int) * (l->capacity - (index + 1));
    memcpy(l->arr + index, l->arr + index + 1, ncopy);
    return ret;
}

void free_list(struct arraylist *l)
{
    if (l) {
        if (l->arr)
            free(l->arr);
        free(l);
    }
}

void print_list(struct arraylist *l)
{
    int i;
    for (i = 0; i < l->size; i++)
        printf("%d ", l->arr[i]);
    printf("\n");
}
