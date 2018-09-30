#include <stdlib.h> /* for malloc, free */

#include "ball.h"

const float circleRadius = 0.025;
const float circleColor = 0;

ball_t *
create_ball(float x, float y, int id)
{
  ball_t *ball = malloc(sizeof(ball_t));
  ball->x = x;
  ball->y = y;
  ball->id = id;
  ball->radius = circleRadius;
  ball->color = circleColor;
  return ball;
}

void
move(ball_t *ball)
{
  ball->x += ball->u;
  ball->y += ball->v;
}

void
destroy_ball(ball_t *ball)
{
  if (ball)
    free(ball);
}
