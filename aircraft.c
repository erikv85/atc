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

float get_bearing(struct aircraft *self)
{
        float u,v;
        u = self->d->xv;
        v = self->d->yv;
        return atan2(v, u) * 180 * M_1_PI;
}

void set_bearing(struct aircraft *self, int bearing)
{
        int degdiff = bearing - (int)get_bearing(self);
        if (degdiff < 0)
                degdiff += 360;
        float t = (float)degdiff * M_PI / 180;
        float u,v;
        u = self->d->xv;
        v = self->d->yv;
        self->d->xv = u * cos(t) - v * sin(t);
        self->d->yv = u * sin(t) + v * cos(t);
}

char *read_cmd(struct aircraft *self, char *cmd)
{
        if (cmd == NULL || cmd[0] != 'i') {
                return NULL;
        } else if ((int)(cmd[1] - '0') == self->id) {
                printf("message meant for %c received by %d\n", cmd[1], self->id);
                char cmd_code = cmd[3];
                char cmd_val = cmd[4];
                float vec_vel = atof(cmd + 4);
                printf("cmd letter: '%c'\n", cmd_code);
                printf("cmd content: '%c'\n", cmd_val);
                printf("cmd content as float: %f\n", vec_vel);
                if (cmd_code == 'v') {
                        float oldvel = get_velocity(self);
                        float angle = get_bearing(self);
                        self->d->xv = vec_vel * cos(angle);
                        self->d->yv = vec_vel * sin(angle);
                        printf("%f\n", get_velocity(self));
                        printf("changed velocity from %f to %f\n", oldvel, get_velocity(self));
                } else if (cmd_code == 'd') {
                        float oldbearing = get_bearing(self);
                        int dbearing = atoi(&cmd[4]);
                        set_bearing(self, dbearing);
                        printf("changed direction from %f to %f\n", oldbearing, get_bearing(self));
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

char *to_string(struct aircraft *self)
{
        sprintf(self->info, "%d -> (x, y, v) = (%f, %f, %f)", \
                        self->id, self->d->xc, self->d->yc, get_velocity(self));
        return self->info;
}

void takeoff(struct aircraft *self)
{
        printf("takeoff!\n");
}
