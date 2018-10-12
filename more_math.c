#include <math.h>

#include "more_math.h"

float *solve_quadratic(float a, float b, float c) {
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
