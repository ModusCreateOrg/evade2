#include "Game.h"

void Starfield::init() {
  //  debug("Starfield::init\n");
  for (int i = 0; i < NUM_STARS; i++) {
    initStar(i);
  }
}

/**
 * Randomly place the star indexed by i in the universe
 */
void Starfield::initStar(int i) {
  starX[i] = 256 - (COORD)random(0, 512) + Camera::x;
  starY[i] = 256 - (COORD)random(0, 512) + Camera::y;
  starZ[i] = Camera::z + (COORD)random(200, 512);
}

void Starfield::render() {
  float cx = Camera::x;
  float cy = Camera::y;
  float cz = Camera::z;

  for (int i = 0; i < NUM_STARS; i++) {
    float zz = (starZ[i] - cz) * 2;
    if (zz < 0) {
      initStar(i);
      zz = (starZ[i] - cz) * 2;
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
  }
}
