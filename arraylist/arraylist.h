#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h> /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

struct arraylist {
        void **arr;      /**< array holding the elements */
        size_t capacity; /**< maximum no. of elems the list can hold */
        int size;        /**< current number of elems */
};

void add(struct arraylist *al, void *x);

void *remove_by_index(struct arraylist *l, int index);

struct arraylist new_list(size_t capacity);

void free_list(struct arraylist *l);

void print_list(struct arraylist *l);

#ifdef __cplusplus
}
#endif

#endif /* ARRAYLIST_H */
