#ifndef COLLISION_H
#define COLLISION_H

/* Point in space if radius = xv = yv = 0
 */
struct disk {
    float xc;
    float yc;
    float radius;
    float xv;
    float yv;
};

struct disk *new_disk(float xc, float yc, float r, float xv, float yv);

void free_disk(struct disk *d);

void move(struct disk *d);

float min(float, float);

float *time_of_collision(struct disk, struct disk);

float *calc_coeffs(struct disk d1, struct disk d2);

float *solve_quadratic(float, float, float);

#endif /* COLLISION_H */
