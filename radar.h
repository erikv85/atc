#ifndef RADAR_H
#define RADAR_H

struct radar {
        float x;
        float y;
        float r;
};

/**
 * @param x Center of radar coverage in x-axis
 * @param y Center of radar coverage in y-ayis
 * @param r Radius of radar coverage from its center
 */
struct radar *new_radar(float x, float y, float r);

/**
 * Null-safe freeing of radar resource.
 */
void free_radar(struct radar *);

#endif /* RADAR_H */
