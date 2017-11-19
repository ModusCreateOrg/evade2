#include "Star.h"

/**
 * Randomizes the position and speed of the star.
 */
void Star::randomize(int xMin, int xMax, int yMin, int yMax, int zMin, int zMax,
                     int speedMin, int speedMax) {
  // Generate random values for the star.
  x = random(xMin, xMax);
  y = random(yMin, yMax);
  z = random(zMin, zMax);
  // old_x = x;
  // old_y = y;
  speed =
      random(speedMin, speedMax + 1); // speedMax is +1 to make it inclusive.
}

/**
 * Updates the position of the star.
 */
void Star::update(int travel) {
  // Update the star's position based on its speed.
  if (travel == 1)
    y -= speed;

  if (travel == 2)
    y += speed;

  if (travel == 3)
    x -= speed;

  if (travel == 4)
    x += speed;
}
