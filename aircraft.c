#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "aircraft.h"

void move_aircraft(struct aircraft *self)
{
        move(self->d);
}

float get_velocity(struct aircraft *self)
{
        float u,v;
        u = self->d->xv;
        v = self->d->yv;
        return sqrt(u * u + v * v);
}

char *read_cmd(struct aircraft *self, char *cmd)
{
        int i = 0;
        if (cmd == NULL || cmd[0] != 'i') {
                return NULL;
        } else if ((int)(cmd[1] - '0') == self->id) {
                printf("message meant for %c received by %d\n", cmd[1], self->id);
                char cmd_code = cmd[3];
                char cmd_val = cmd[4];
                float foo_val = (float)(cmd_val - '0'); // FIXME
                printf("cmd letter: '%c'\n", cmd_code);
                printf("cmd content: '%c'\n", cmd_val);
                printf("cmd content as float: %f (%c)\n", foo_val, (cmd_val - '0'));
                if (cmd_code == 'v') {
                        printf("changing velocity from %f to ", get_velocity(self));
                        self->d->xv *= foo_val;
                        self->d->yv *= foo_val;
                        printf("%f\n", get_velocity(self));
                } else {
                        printf("ignoring non-velocity command code");
                }
                return NULL;
        } else {
                printf("overheard: message meant for %c received by %d\n", cmd[1], self->id);
                return NULL;
        }
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
