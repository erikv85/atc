/**
 * 1D simplification of an ATC system.
 * NOTE: This file started out as a copy of the 1D version that
 * didn't have graphics.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* sleep */
#include <fcntl.h>
#include <string.h> /* strcmp, strlen */

#include "graphics.h"
#include "ball.h"

int main(int argc, char **argv)
{
  int graphics = 1; /* graphics is on by default */
  if (argc > 1)
    graphics = atoi(argv[1]);

  /* set up params that radar and ctrl both need */
  const float SECTOR_START = 0;
  const float SECTOR_END = 1;
  const int READ_END = 0;        /* read end of a pipe */
  const int WRITE_END = 1;       /* write end of a pipe */

  /* set up pipes */
  int ctrl2rad[2]; /* used by ctrl to write to radar */
  int rad2ctrl[2]; /* used by radar to write to ctrl */

  /* "start" pipes */
  pipe(ctrl2rad);
  pipe(rad2ctrl);

  /* radar should not block when reading msgs from control */
  if (fcntl(ctrl2rad[READ_END], F_SETFL, O_NONBLOCK) == -1) {
    fprintf(stderr, "Call to fcntl failed.\n");
    return -1;
  }

  /* fork and get started */
  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Call to fork failed.\n");
    return -1;
  }
  else if (pid == 0) { /* the radar is the child process */
    close(ctrl2rad[WRITE_END]);
    close(rad2ctrl[READ_END]);
    char ctrl_msg[10] = { '\0' };

    float x = 0;    /* starting position */
    float v = 0.1;  /* starting velocity */
    ball_t *ball = create_ball(x, 0.5, 1); // hardcoded y-pos for now
    ball->u = v;
    float vnew = 0; /* radar will read new velocity into this var */

    if (graphics)
      InitializeGraphics(argv[0], 400, 400);
    while (ball->x >= SECTOR_START && ball->x <= SECTOR_END) {
      move(ball);
      if (graphics) {
        ClearScreen();
        DrawCircle(ball->x, ball->y, 1, 1, ball->radius, ball->color);
        Refresh();
      }
      sleep(1);

      /*
       * Check if controller has left a message. If he has, check if
       * its format is correct. If it is correct, read the new
       * velocity, update velocity, and send ACK to control. If the
       * message does not have a correct format, send NACK to
       * control. Finally, if control has not left a message, do
       * nothing.
       */
      read(ctrl2rad[READ_END], ctrl_msg, 10); /* read 10B from pipe to ctrl_msg */
      if (ctrl_msg[0] == '\0')
        ;
      else if (ctrl_msg[0] != '\0') {
        if (ctrl_msg[0] != 'v') {
          printf("Incorrect message format '%s', sending NACK.\n", ctrl_msg);
          write(rad2ctrl[WRITE_END], "NACK", 5);
        }
        else if (ctrl_msg[0] == 'v') {
          vnew = atof(ctrl_msg+2);
          ball->u = vnew;
          printf("Correct message format '%s', updating velocity to %f " \
            "and sending ACK.\n", ctrl_msg, ball->u);
          write(rad2ctrl[WRITE_END], "ACK", 5);
        }
        else { //this should not happen
          fprintf(stderr, "A message was read but neither ACK nor " \
            "NACK was returned to control.\n");
        }
        /* reset the message */
        ctrl_msg[0] = '\0';
      }
      else { //this should not happen
        fprintf(stderr, "The message '%s' registered neither as NULL " \
          "nor non-NULL\n", ctrl_msg);
      }
    }
    if (graphics) {
      FlushDisplay();
      CloseDisplay();
    }
    printf("No more traffic in sector.\n");
  }
  else {               /* Control is the parent process */
    close(ctrl2rad[READ_END]);
    close(rad2ctrl[WRITE_END]);

    char user_input[10];
    char radar_response[5];

    // TODO: add description of how controller loop works
    while (1) {
      scanf("%s", user_input); /* protocol: v-<velocity><Enter> */
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