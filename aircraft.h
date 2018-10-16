#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "radar.h"
#include "collision.h"

struct aircraft {
        struct disk *d;
        int freq;
        int id;
};

float get_velocity(struct aircraft *self);

char *read_cmd(struct aircraft *self, char *cmd);

struct aircraft *new_aircraft(float xc, float yc, float r, float xv, float yv);

void set_freq(struct aircraft *self, int freq);

void set_id(struct aircraft *self, int id);

/**
 * We have an aircraft/disk d. d stands at gate. d must register
 * itself with tower, meaning it must transmit its details to tower's
 * radio frequency.
 *
 * Tower shall confirm d's transmission.
 *
 * ATC can call aircraft registered with a certain frequency. More
 * specifically, all aircraft registered with a frequency will also be
 * listening on that frequency, meaning a call to the frequency is
 * heard (and analyzed) by all aircraft.
 *
 * FIXME: Analyzing ATController calls for identity can be postponed,
 * as we'll need to make sure everything else works fine for one or two
 * aircraft first.
 *
 * At this point, controller-aircraft interaction must be acknowledged
 * both ways. We shall belay emergency calls from aircraft till later,
 * for now we assume that controller initiates all communication, and
 * the intended recipient (an aircraft) either acknowledges and
 * executes the communicated command, or acknowledges (through a NACK)
 * that the communication could not be interpreted.
 */

int register_closest_radar();

/**
 * Aircraft can use this function to broadcast its presence to
 * anyone who's listening. Responses may occur in any order, but
 * aircraft shall register with closest responder.
 */
void broadcast_presence(struct aircraft *self);

/**
 * Register with a known radar.
 */
int register_with_radar(struct radar *rdr);

void move_aircraft(struct aircraft *self);

void free_aircraft(struct aircraft *ac);

#endif /* AIRCRAFT_H */
