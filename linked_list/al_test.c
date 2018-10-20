#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "aircraft.h"

void main()
{
        : // disallow compilation till list_t is fixed
        list_t **l = malloc(sizeof(struct node *));
        print_list(l);
        float radius = 0.005;
        struct aircraft *acs[6];
        int i;
        for (i = 0; i < 6; i++) {
                acs[i] = new_aircraft(0, 0.5, radius, 0.01, 0);
                set_id(acs[i], i + 1);
                push(acs[i], l);
                print_list(l);
        }
        printf("%s\n", to_string(pop(l)));
        print_list(l);

        printf("0th item: %s\n", to_string(get(l, 0)));
        printf("1st item: %s\n", to_string(get(l, 1)));
        printf("2nd item: %s\n", to_string(get(l, 2)));
        printf("last item: %s\n", to_string(get(l, size(l) - 1)));
        printf("removed %s\n", to_string(remove_by_index(l, 0)));
        printf("size: %d\n", size(l));
        printf("removed %s\n", to_string(remove_by_index(l, size(l) - 1)));
        //printf("removed %s\n", remove_by_value(l, 5));
        print_list(l);
        l = free_list(l);
        printf("l addr: %p\n", l);
        print_list(l);
}
