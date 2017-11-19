#include "Game.h"

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef SHOW_FPS
long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;
#endif

// Global variables.
Arduboy2 arduboy;
Starfield starfield;

void setup(void) {
  // initiate arduboy instance
  arduboy.boot();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(60);
  arduboy.clear();
  starfield.init();
  ProcessManager::init();
  ObjectManager::init();
}

float vz = 1;

void loop(void) {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  if (arduboy.pressed(A_BUTTON)) {
    vz -= .1;
    if (vz < 1) {
      vz = 1;
    }
  }
  if (arduboy.pressed(B_BUTTON)) {
    vz += .1;
    if (vz > 25) {
      vz = 25;
    }
  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    Camera::x -= 1;
  }
  if (arduboy.pressed(LEFT_BUTTON)) {
    Camera::x += 1;
  }
  if (arduboy.pressed(DOWN_BUTTON)) {
    Camera::y += 1;
  }
  if (arduboy.pressed(UP_BUTTON)) {
    Camera::y -= 1;
  }

  Camera::z += vz;
  starfield.render();
  ProcessManager::run();
  ObjectManager::run();

#ifdef SHOW_FPS
  fpsCounter++;
  long actualTime = millis();
  if ((fpsCounter % 30) == 0) {
    if (previousTime != 0) {
      fps = (30 * 1000 / (actualTime - previousTime));
    }
    previousTime = actualTime;
    fpsCounter = 0;
  }

  arduboy.setCursor(116, 4);
  arduboy.print(fps);
#endif

  // then we finaly we tell the arduboy to display what we just wrote to the
  // display
  arduboy.display(TRUE);
}
