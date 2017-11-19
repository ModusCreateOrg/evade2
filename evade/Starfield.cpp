#include "Game.h"

void Starfield::init() {
  for (int i = 0; i < NUM_STARS; i++) {
    starX[i] = (COORD)random(1, 256);
    starY[i] = (COORD)random(1, 256);
    starZ[i] = (COORD)random(1, 256);
  }
}

void Starfield::render() {
  float cx = Camera::x;
  float cy = Camera::y;
  float cz = Camera::z;

  for (int i = 0; i < NUM_STARS; i++) {
    float zz = (starZ[i] - cz) * 2;
    if (zz < 0) {
      starX[i] = (COORD)random(1, 256);
      starY[i] = (COORD)random(1, 256);
      starZ[i] = Camera::z + (COORD)random(1, 256);
      continue;
    }
    float ratioX = SCREEN_WIDTH / (zz + SCREEN_WIDTH);
    float ratioY = SCREEN_HEIGHT / (zz + SCREEN_HEIGHT);
    float x = starX[i] * ratioX;
    float y = starY[i] * ratioY;
    //    debug("star %d %f,%f x,y,z %d,%d,%d => %f,%f\n", i, ratioX, ratioY, starX[i], starY[i], starZ[i], x, y);
    arduboy.drawPixel((WORD)x, (WORD)y, WHITE);
  }
}
