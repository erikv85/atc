#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "collision.h"

void move_disk(struct disk *d) {
    d->xc += d->xv;
    d->yc += d->yv;
}

float *solve_quadratic(float a, float b, float c) {
    float denom = 2 * a;
    float discr = b * b - 4 * a * c;
    if (denom == 0 || discr < 0) { // NaN or non-real roots
        return NULL;
    }
    else {
        float *x = malloc(2 * sizeof(float));
        *x = (-b + sqrt(discr))/denom;
        *(x + 1) = (-b - sqrt(discr))/denom;
        return x;
    }
}

float *calc_coeffs(struct disk d1, struct disk d2) {
    float x10,x20,y10,y20,u1,u2,v1,v2,r1,r2;
    x10 = d1.xc;
    x20 = d2.xc;
    y10 = d1.yc;
    y20 = d2.yc;
    u1 = d1.xv;
    u2 = d2.xv;
    v1 = d1.yv;
    v2 = d2.yv;
    r1 = d1.radius;
    r2 = d2.radius;
    float a,b,c;
    a = (u1 - u2) * (u1 - u2) + (v1 - v2) * (v1 - v2);
    c = (x10 - x20) * (x10 - x20) + (y10 - y20) * (y10 - y20) - (r1 + r2) * (r1 + r2);
    float bx = u1 * x10 + u2 * x20 - u1 * x20 - u2 * x10;
    float by = v1 * y10 + v2 * y20 - v1 * y20 - v2 * y10;
    b = 2 * (bx + by);
    float *coeffs = malloc(3 * sizeof(float));
    *coeffs = a;
    *(coeffs + 1) = b;
    *(coeffs + 2) = c;
    return coeffs;
}

float *time_of_collision(struct disk d1, struct disk d2) {
    float *coeffs = calc_coeffs(d1, d2);
    float a,b,c;
    a = *coeffs;
    b = *(coeffs + 1);
    c = *(coeffs + 2);
    free(coeffs);
    return solve_quadratic(a, b, c);
}

float min(float a, float b) {
    return a <= b ? a : b;
}
