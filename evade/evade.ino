#include "Game.h"

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef SHOW_FPS
long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;
#endif

// Global variables.
Arduboy2 arduboy;
BYTE frameCounter = 0;

void setup(void) {
  // initiate arduboy instance
  arduboy.boot();
  arduboy.flashlight();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(FRAMERATE);

  Sound::init();
  arduboy.clear();
  Starfield::init();
  ProcessManager::init();
  ObjectManager::init();

  ProcessManager::birth(splash_process, PTYPE_SYSTEM);
  //  ProcessManager::birth(player_process, PTYPE_SYSTEM);
  //  ProcessManager::birth(fighter1_process);

  Sound::play_score(DEMO_SCORE);
}

void loop(void) {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  frameCounter++;
  Controls::run();
  Camera::move();
  Starfield::render();
  ProcessManager::run();
  ObjectManager::run();

  HUD::draw();
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
  arduboy.setTextSize(1);
  arduboy.print(fps);
#endif

// then we finaly we tell the arduboy to display what we just wrote to the
// display
// TODO instead of erasing the entire screen to black here, maybe we can erase the stars and lines
#if TRUE
  arduboy.display(TRUE);
#else
  arduboy.display();
  ObjectManager::erase();
#endif
}
