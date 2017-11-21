#include "Game.h"

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef SHOW_FPS
long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;
#endif

struct atm_sfx_state sfx_state;

// Global variables.
Arduboy2 arduboy;
Controls controls;
Starfield starfield;

void setup(void) {
  // initiate arduboy instance
  arduboy.boot();
  arduboy.initRandomSeed();
  arduboy.setFrameRate(FRAMERATE);

  // Initialize audio system
  arduboy.audio.on();

  // Initialize ATMLib2
  atm_synth_setup();

  arduboy.clear();
  starfield.init();
  ProcessManager::init();
  ObjectManager::init();

  ProcessManager::birth(fighter1_process);
  Camera::vz = CAMERA_VZ;

  // Play a song
  atm_synth_play_score((const uint8_t *)&score);
}

void loop(void) {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  // controls
  controls.run();
  if (controls.debounced(BUTTON_A)) {
    ProcessManager::birth(bullet_process);

    // Play SFX
    atm_synth_play_sfx_track(OSC_CH_TWO, (const uint8_t *)&pew, &sfx_state);
  }
  //  if (arduboy.pressed(B_BUTTON)) {
  //    vz += .1;
  //    if (vz > 25) {
  //      vz = 25;
  //    }
  //  }
  if (arduboy.pressed(RIGHT_BUTTON)) {
    Camera::vx = -DELTACONTROL;
  }
  else if (arduboy.pressed(LEFT_BUTTON)) {
    Camera::vx = DELTACONTROL;
  }
  else {
    Camera::vx = 0;
  }

  if (arduboy.pressed(DOWN_BUTTON)) {
    Camera::vy = DELTACONTROL;
  }
  else if (arduboy.pressed(UP_BUTTON)) {
    Camera::vy = -DELTACONTROL;
  }
  else {
    Camera::vy = 0;
  }

  // render
  Camera::move();
  starfield.render();
  ObjectManager::run();
  ProcessManager::run();

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
