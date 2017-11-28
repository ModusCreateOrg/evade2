#include "Game.h"

WORD Starfield::starX[NUM_STARS],
    Starfield::starY[NUM_STARS];
FLOAT Starfield::starZ[NUM_STARS];

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
  starX[i] = 256 - random(0, 512) + Camera::x;
  starY[i] = 256 - random(0, 512) + Camera::y;
  starZ[i] = Camera::z + random(200, 512);
}

void Starfield::render() {
  FLOAT cz = Camera::z;

  for (int i = 0; i < NUM_STARS; i++) {
    FLOAT zz = (starZ[i] - cz) * 2;
    if (zz < 0) {
      initStar(i);
      zz = (starZ[i] - cz) * 2;
    }
    FLOAT ratioX = SCREEN_WIDTH / (zz + SCREEN_WIDTH);
    FLOAT ratioY = SCREEN_HEIGHT / (zz + SCREEN_HEIGHT);
    FLOAT x = (SCREEN_WIDTH / 2) - (starX[i] - Camera::x) * ratioX;
    FLOAT y = (SCREEN_HEIGHT / 2) - (starY[i] - Camera::y) * ratioY;
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
      initStar(i);
    }
    else {
      Graphics::drawPixel((WORD)x, (WORD)y);
    }
  }
}
