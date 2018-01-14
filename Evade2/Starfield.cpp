#include "Evade2.h"

FXP_WORLD_COORD Starfield::starX[NUM_STARS], Starfield::starY[NUM_STARS];
FXP_WORLD_COORD Starfield::starZ[NUM_STARS];

void Starfield::init() {
  for (int i = 0; i < NUM_STARS; i++) {
    initStar(i);
  }
}

/**
 * Randomly place the star indexed by i in the universe
 */
void Starfield::initStar(int i) {
  starX[i] = 256 - random(0, 512) + Camera::x;
  starY[i] = 128 - random(0, 256) + Camera::y;
  starZ[i] = Camera::z + random(0, 255);
}

void Starfield::render() {
  const FXP_WORLD_COORD cz = Camera::z;

  for (int i = 0; i < NUM_STARS; i++) {
    FXP_WORLD_COORD zz = (starZ[i] - cz);
    if (zz <= 0) {
      initStar(i);
      continue;
    }
    int16_t ratio = (~zz) & 0xff;
    DISPLAY_S_COORD x = (SCREEN_WIDTH / 2) - DISPLAY_S_COORD(((starX[i] - Camera::x) * ratio)>>8);
    DISPLAY_S_COORD y = (SCREEN_HEIGHT / 2) - DISPLAY_S_COORD(((starY[i] - Camera::y) * ratio)>>8);
    if (x & ~0x7f || y & ~0x3f) {
      initStar(i);
    }
    else {
      Graphics::drawPixel((WORD)x, (WORD)y);
    }
  }
}
