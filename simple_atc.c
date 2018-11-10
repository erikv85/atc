#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */
#include <fcntl.h>
#include <string.h> /* strcmp, strlen */

#include "aircraft.h"
#include "graphics.h"
#include "arraylist.h"

const float SECTOR_START = 0;
const float SECTOR_END = 1;

float time_scale = 10000;

void draw_aircrafts(struct arraylist ac_list);

int out_of_bounds(struct aircraft *ac);

int main(int argc, char **argv)
{
        int graphics = 1;
        if (argc > 1) {
                graphics = atoi(argv[1]);
        }

        /* set up params that radar and ctrl both need */
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
                float radius = 0.005;
                acs[0] = new_aircraft(0, 0.5, radius, 0.01 / time_scale, 0);
                set_freq(acs[0], 100);
                set_id(acs[0], 1);
                acs[1] = new_aircraft(1, 0.75, radius, -0.005 / time_scale, 0);
                set_freq(acs[1], 100);
                set_id(acs[1], 2);

                struct arraylist al = new_list(1);
                add(&al, acs[0]);
                add(&al, acs[1]);

                int report_interval = 10 * time_scale;
                int time = 0;
                if (graphics)
                        InitializeGraphics(argv[0], 400, 400);
                while (al.size > 0) {
                        if (graphics)
                                draw_aircrafts(al);
                        read(ctrl2rad[READ_END], ctrl_msg, 10);
                        int i;
                        for (i = 0; i < al.size; i++) {
                                // Check for messages. The message is out in the "ether", every
                                // pilot must analyze its contents and applicability. Sample
                                // command: "i1|v2" (without quotes) - this means that aircraft
                                // with id 1 shall set speed to 2.
                                // reset the message
                                read_cmd(al.arr[i], ctrl_msg);
                                move_aircraft(al.arr[i]);
                                if (!(time % report_interval)) {
                                        printf("%s\n", to_string(al.arr[i]));
                                }
                                if (out_of_bounds(al.arr[i])) {
                                        printf("%d left radar\n",
                                                        ((struct aircraft *)al.arr[i])->id);
                                        free_aircraft(al.arr[i]);
                                        remove_by_index(&al, i);
                                }
                        }
                        time = (time + 1) % report_interval;
                        ctrl_msg[0] = '\0';
                }
                if (graphics) {
                        EndGraphics();
                }
                printf("No more traffic in sector.\n");
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

int out_of_bounds(struct aircraft *ac)
{
        float x,y;
        x = ac->d->xc;
        y = ac->d->yc;
        return (x < SECTOR_START || x > SECTOR_END || y < SECTOR_START || y > SECTOR_END);
}
void draw_aircrafts(struct arraylist ac_list)
{
        int i;
        ClearScreen();
        for (i = 0; i < ac_list.size; i++) {
                struct aircraft *curr_ac = (struct aircraft *)ac_list.arr[i];
                DrawCircle(curr_ac->d->xc, curr_ac->d->yc, 1, 1, curr_ac->d->radius, 0);
        }
        Refresh();
}
