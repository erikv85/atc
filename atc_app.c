#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "radar.h"
#include "aircraft.h"

int main(int argc, char **argv)
{
        printf("argc = %d\n", argc);
        int naircraft = 0;
        if (argc > 1)
                naircraft = atoi(argv[1]);
        printf("naircraft = %d\n", naircraft);
        if (naircraft < 1) {
                printf("no aircraft in sector, ending...\n");
                return 0;
        }

        struct radar *rdr = new_radar(0, 0, 1);
        struct aircraft **aircraft = malloc(naircraft * sizeof(struct aircraft));
        int i = 0;
        for (i = 0; i < naircraft; i++) {
                aircraft[i] = new_aircraft(0, 0, 0.025, 0, 0);
        }

        pid_t pid = fork();
        if (pid < 0) {
                fprintf(stderr, "fork failed, exiting...");
                return -1;
        } else if (pid == 0) {
                for (i = 0; i < naircraft; i++)
                        takeoff(aircraft[i]);
        } else {
        }
}
