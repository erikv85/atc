#include <stdlib.h>

#include "radar.h"

struct radar *new_radar(float x, float y, float r) {
        struct radar *rdr = malloc(sizeof(struct radar));
        rdr->x = x;
        rdr->y = y;
        rdr->r = r;
        return rdr;
}

void free_radar(struct radar *rdr) {
        if (rdr)
                free(rdr);
}
