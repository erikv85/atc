#include <stdlib.h>
#include <math.h>

#include "collision.h"

void move(struct disk *d)
{
        d->xc += d->xv;
        d->yc += d->yv;
}

/**
 * Solves the quadratic polynomial ax^2 + bx + c.
 *
 * @return The roots of the specified polynomial. If either 2a or the
 * discriminant are zero, this function returns NULL.
 */
float *solve_quadratic(float a, float b, float c)
{
        float denom = 2 * a;
        float discr = b * b - 4 * a * c;
        if (denom == 0 || discr < 0) { // NaN or non-real roots
                return NULL;
        } else {
                float *x = malloc(2 * sizeof(float));
                *x = (-b + sqrt(discr))/denom;
                *(x + 1) = (-b - sqrt(discr))/denom;
                return x;
        }
}

float *calc_coeffs(struct disk d1, struct disk d2)
{
        float a = (d1.xv - d2.xv) * (d1.xv - d2.xv) + (d1.yv - d2.yv) * (d1.yv - d2.yv);
        float c = (d1.xc - d2.xc) * (d1.xc - d2.xc) + (d1.yc - d2.yc) * (d1.yc - d2.yc) - (d1.radius + d2.radius) * (d1.radius + d2.radius);
        float bx = d1.xv * d1.xc + d2.xv * d2.xc - d1.xv * d2.xc - d2.xv * d1.xc;
        float by = d1.yv * d1.yc + d2.yv * d2.yc - d1.yv * d2.yc - d2.yv * d1.yc;
        float *coeffs = malloc(3 * sizeof(float));
        *coeffs = a;
        *(coeffs + 1) = 2 * (bx + by);
        *(coeffs + 2) = c;
        return coeffs;
}

/**
 * Calculate the time of collision of two disks.
 *
 * @return The two possible points of collision...
 */
float *time_of_collision(struct disk d1, struct disk d2)
{
        float *coeffs = calc_coeffs(d1, d2);
        float a,b,c;
        a = *coeffs;
        b = *(coeffs + 1);
        c = *(coeffs + 2);
        free(coeffs);
        return solve_quadratic(a, b, c);
}

struct disk *new_disk(float xc, float yc, float r, float xv, float yv)
{
        struct disk *d = malloc(sizeof(struct disk));
        d->xc = xc;
        d->yc = yc;
        d->radius = r;
        d->xv = xv;
        d->yv = yv;
        return d;
}

void free_disk(struct disk *d)
{
        if (d)
                free(d);
}

float min(float a, float b)
{
        return a <= b ? a : b;
}
