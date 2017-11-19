#include "Game.h"

#ifdef DEV
static int counter = 0;
#endif

void Starfield::init() {
  debug("Starfield::init\n");
  for (int i = 0; i < NUM_STARS; i++) {
    initStar(i);
    //    starX[i] = 128 - (COORD)random(0, 255);
    //    starY[i] = 128 - (COORD)random(0, 255);
    //    starZ[i] = Camera::z + (COORD)random(128, 255);
  }
}

void Starfield::initStar(int i) {
  //    starX[i] = 128 - (COORD)random(0, 255);
  //    starY[i] = 128 - (COORD)random(0, 255);
  //    starZ[i] = Camera::z + (COORD)random(128, 255);
  starX[i] = 128 - (COORD)random(0, 255) + Camera::x;
  starY[i] = 128 - (COORD)random(0, 255) + Camera::y;
  starZ[i] = Camera::z + (COORD)random(128, 255);
}

void Starfield::render() {
  float cx = Camera::x;
  float cy = Camera::y;
  float cz = Camera::z;

#ifdef DEV
  counter++;
#endif

  for (int i = 0; i < NUM_STARS; i++) {
    float zz = (starZ[i] - cz) * 2;
    if (zz < 0) {
      debug("reset %d #%d\n", counter, i);
      initStar(i);
      //      starX[i] = 128 - (COORD)random(0, 255) + Camera::x;
      //      starY[i] = 128 - (COORD)random(0, 255) + Camera::y;
      //      starZ[i] = Camera::z + (COORD)random(128, 255);
      continue;
    }
    float ratioX = SCREEN_WIDTH / (zz + SCREEN_WIDTH);
    float ratioY = SCREEN_HEIGHT / (zz + SCREEN_HEIGHT);
    float x = (SCREEN_WIDTH / 2) - (starX[i] - Camera::x) * ratioX;
    float y = (SCREEN_HEIGHT / 2) - (starY[i] - Camera::y) * ratioY;
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
      initStar(i);
    }
    else {
      arduboy.drawPixel((WORD)x, (WORD)y, WHITE);
    }
    //    debug("star %d %f,%f x,y,z %d,%d,%d => %f,%f\n", i, ratioX, ratioY, starX[i], starY[i], starZ[i], x, y);
  }
}
