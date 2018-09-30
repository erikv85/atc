#include <stdio.h>

#include "graphics.h"
#include "collision.h"

int main(int argc, char **argv) {
    struct disk d1 = { 0.025, 0.75, 0.025, 0.000001, -0.000001 };
    struct disk d2 = { 0.025, 0.25, 0.025, 0.000001, 0.000001 };
    InitializeGraphics(argv[0], 400, 400);
    while (1) {
        ClearScreen();
        DrawCircle(d1.xc, d1.yc, 1, 1, d1.radius, 0);
        DrawCircle(d2.xc, d2.yc, 1, 1, d2.radius, 0);
        float *times = time_of_collision(d1, d2);
        float t_min = min(times[0], times[1]);
        if (t_min > 0)
            printf("Collision in %f seconds\n", t_min);
        free(times);
        Refresh();
        move(&d1);
        move(&d2);
    }
    FlushDisplay();
    CloseDisplay();
    return 0;
}
