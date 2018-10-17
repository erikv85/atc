#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */
#include <fcntl.h>
#include <string.h> /* strcmp, strlen */

#include "aircraft.h"
#include "graphics.h"

void clear_draw_refresh(int naircraft, struct aircraft **acs);

void end_graphics();

int main(int argc, char **argv)
{
        int graphics = 1;
        if (argc > 1) {
                graphics = atoi(argv[1]);
        }

        /* set up params that radar and ctrl both need */
        const float SECTOR_START = 0;
        const float SECTOR_END = 1;
        const int READ_END = 0;
        const int WRITE_END = 1;

        /* set up pipes */
        int ctrl2rad[2]; /* used by ctrl to write to radar */
        int rad2ctrl[2]; /* used by radar to write to ctrl */
        pipe(ctrl2rad);
        pipe(rad2ctrl);

        /* reading should not block */
        if (fcntl(ctrl2rad[READ_END], F_SETFL, O_NONBLOCK) == -1) {
                fprintf(stderr, "Call to fcntl failed.\n");
                return -1;
        }
        if (fcntl(rad2ctrl[READ_END], F_SETFL, O_NONBLOCK) == -1) {
                fprintf(stderr, "Call to fcntl failed.\n");
                return -1;
        }

        int naircraft = 2; // TODO: make as arg

        pid_t pid = fork();
        if (pid < 0) {
                fprintf(stderr, "Call to fork failed.\n");
                return -1;
        } else if (pid == 0) { /* the radar is the child process */
                /* TODO:
                 * char *fdstr[3];
                 * fdstr[0] = ctrl2rad;
                 * fdstr[1] = ctrl2rad;
                 * fdstr[2] = 0;
                 * execv("aircraft_main", fdstr);
                 */
                close(ctrl2rad[WRITE_END]);
                close(rad2ctrl[READ_END]);
                char ctrl_msg[10] = { '\0' };

                struct aircraft *acs[naircraft];
                acs[0] = new_aircraft(0, 0.5, 0.025, 0.01, 0);
                set_freq(acs[0], 100);
                set_id(acs[0], 1);
                acs[1] = new_aircraft(1, 0.75, 0.025, -0.005, 0);
                set_freq(acs[1], 100);
                set_id(acs[1], 2);

                int report_interval = 10;
                int time = 0;
                if (graphics)
                        InitializeGraphics(argv[0], 400, 400);
                while (acs[0]->d->xc >= SECTOR_START && acs[0]->d->xc <= SECTOR_END) {
                        if (graphics) {
                                clear_draw_refresh(naircraft, acs);
                        }
                        read(ctrl2rad[READ_END], ctrl_msg, 10);
                        int i;
                        for (i = 0; i < naircraft; i++) {
                                // Check for messages. The message is out in the "ether", every
                                // pilot must analyze its contents and applicability. Sample
                                // command: "i1|v2" (without quotes) - this means that aircraft
                                // with id 1 shall set speed to 2.
                                // reset the message
                                read_cmd(acs[i], ctrl_msg);
                                move_aircraft(acs[i]);
                                if (!(time % report_interval)) {
                                        report_status(acs[i]);
                                }
                        }
                        time = (time + 1) % report_interval;
                        sleep(1);
                        ctrl_msg[0] = '\0';
                }
                if (graphics) {
                        end_graphics();
                }
                printf("No more traffic in sector.\n");
                free_aircraft(acs[0]);
                free_aircraft(acs[1]);
        } else { /* Control is the parent process */
                close(ctrl2rad[READ_END]);
                close(rad2ctrl[WRITE_END]);

                char user_input[10];
                char radar_response[5];

                // TODO: add description of how controller loop works
                while (1) {
                        scanf("%s", user_input);
                        write(ctrl2rad[WRITE_END], user_input, 10);
                        read(rad2ctrl[READ_END], radar_response, 5);
                        if (strcmp(radar_response, "ACK") == 0)
                                printf("CONTROL: Received ACK\n");
                        else if (strcmp(radar_response, "NACK") == 0)
                                printf("CONTROL: Received NACK\n");
                        else //this should not happen
                                fprintf(stderr, "CONTROL: Received %s of length %d\n", \
                                        radar_response, (int)strlen(radar_response));
                }
        }

        return 0;
}

void clear_draw_refresh(int naircraft, struct aircraft **acs)
{
        int i;
        ClearScreen();
        for (i = 0; i < naircraft; i++) {
                DrawCircle(acs[i]->d->xc, acs[i]->d->yc, 1, 1, acs[i]->d->radius, 0);
        }
        Refresh();
}

void end_graphics()
{
        FlushDisplay();
        CloseDisplay();
}
