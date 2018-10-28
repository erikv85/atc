#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h> /* size_t */

struct arraylist {
        int *arr;        /**< array holding the elements */
        size_t capacity; /**< maximum no. of elems the list can hold */
        int size;        /**< current number of elems */
};

void add(struct arraylist *al, int x);

int remove_by_index(struct arraylist *l, int index);

struct arraylist *new_list(size_t capacity);

void free_list(struct arraylist *l);

void print_list(struct arraylist *l);

#endif /* ARRAYLIST_H */
