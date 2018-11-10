#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "aircraft.h"

extern float time_scale;

const double DEG_TO_RAD = M_PI / 180;

void move_aircraft(struct aircraft *self)
{
        move(self->d);
}

float get_velocity(struct aircraft *self)
{
        float u = self->d->xv;
        float v = self->d->yv;
        return sqrt(u * u + v * v);
}

void set_velocity(struct aircraft *self, float vp)
{
        float t = get_bearing(self);
        self->d->xv = vp * cos(t);
        self->d->yv = vp * sin(t);
}

/**
 * @return Bearing in radians
 */
float get_bearing(struct aircraft *self)
{
        //if x component isn't too close to zero
        return atan2(self->d->yv, self->d->xv);
        //else do magic
}

/**
 * @param bearing Bearing in radians
 */
void set_bearing(struct aircraft *self, float bearing)
{
        float curr_bearing = get_bearing(self);
        float d = bearing - curr_bearing;
        float cosd = cos(d);
        float sind = sin(d);
        float u = self->d->xv;
        float v = self->d->yv;
        self->d->xv = u * cosd - v * sind;
        self->d->yv = u * sind + v * cosd;
}

char *read_cmd(struct aircraft *self, char *cmd)
{
        if (cmd == NULL || cmd[0] != 'i') {
                ;
        } else if ((int)(cmd[1] - '0') == self->id) {
                char cmd_code = cmd[3];
                char cmd_val = cmd[4];
                float vec_vel = atof(cmd + 4);
                printf("cmd letter: '%c'\n", cmd_code);
                if (cmd_code == 'v') {
                        float oldvel = get_velocity(self);
                        set_velocity(self, vec_vel / time_scale);
                        printf("%d: changed velocity from %f to %f\n",
                                        self->id, oldvel, get_velocity(self));
                } else if (cmd_code == 'd') {
                        float oldbearing = get_bearing(self);
                        float rad_bearing = atof(cmd + 4) * DEG_TO_RAD;
                        set_bearing(self, rad_bearing);
                        printf("%d: changed direction from %f to %f\n",
                                        self->id, oldbearing, get_bearing(self));
                } else {
                        printf("%d: ignoring non-velocity command code",
                                        self->id);
                }
        }
        return NULL;
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
        float rbearing = get_bearing(self);
        float dbearing = rbearing * 180 * M_1_PI;
        if (dbearing < 0)
                dbearing += 360;
        sprintf(self->info, "%d -> (x, y, v, d) = (%f, %f, %.3f, %3.0f (%.2f))",
                        self->id, self->d->xc, self->d->yc,
                        get_velocity(self) * time_scale, dbearing, rbearing);
        return self->info;
}

void takeoff(struct aircraft *self)
{
        printf("takeoff!\n");
}
