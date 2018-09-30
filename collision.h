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

void move_disk(struct disk *d);

float min(float, float);

float *time_of_collision(struct disk, struct disk);

float *calc_coeffs(struct disk d1, struct disk d2);

float *solve_quadratic(float, float, float);

#endif /* COLLISION_H */
