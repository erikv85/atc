#include <stdio.h>
#include <stdlib.h>

#include "aircraft.h"

struct aircraft *new_aircraft(float xc, float yc, float r, float xv, float yv)
{
        struct aircraft *ac = malloc(sizeof(struct aircraft));
        (ac->d).xc = xc;
        return ac;
}

void free_aircraft(struct aircraft *ac)
{
        if (ac)
                free(ac);
}

void takeoff(struct aircraft *self)
{
        printf("takeoff!\n");
}
