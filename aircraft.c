#include <stdio.h>
#include <stdlib.h>

#include "aircraft.h"

void move_aircraft(struct aircraft *self)
{
        move(self->d);
}

struct aircraft *new_aircraft(float xc, float yc, float r, float xv, float yv)
{
        struct aircraft *ac = malloc(sizeof(struct aircraft));
        ac->d = new_disk(xc, yc, r, xv, yv);
        return ac;
}

void set_freq(struct aircraft *self, int freq)
{
        self->freq = freq;
}

void set_id(struct aircraft *self, int id)
{
        self->id = id;
}

void free_aircraft(struct aircraft *ac)
{
        if (ac) {
                if (ac->d)
                        free(ac->d);
                free(ac);
        }
}

void takeoff(struct aircraft *self)
{
        printf("takeoff!\n");
}
