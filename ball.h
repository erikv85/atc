#ifndef BALL_H
#define BALL_H

/*
 * Constant radius and color till I get a better hang of the graphics
 * routines.
 */
extern const float circleRadius;
extern const float circleColor; // corresponds to black

typedef struct {
  int id;
  float x, y;
  float radius, color;
  float u, v;
} ball_t;

ball_t *create_ball(float x, float y, int id);

/**
 * @brief Move ball according to its speed
 *
 * @param ball Pointer to the ball to be moved
 */
void move(ball_t *ball);

void destroy_ball(ball_t *ball);

#endif /* BALL_H */
