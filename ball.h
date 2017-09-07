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

/**
 * @brief Move ball to specific position
 *
 * @param ball Pointer to the ball to be moved
 * @param destx x-coordinate to move ball to
 * @param desty y-coordinate to move ball to
 */
void moveTo(ball_t *ball, float destx, float desty);

/**
 * @brief Move ball by specified steps
 *
 * @param ball Pointer to the ball to be moved
 * @param xstep Step size in the x-direction
 * @param ystep Step size in the y-direction
 */
void moveByStep(ball_t *ball, float xstep, float ystep);

void destroy_ball(ball_t *ball);

#endif /* BALL_H */
