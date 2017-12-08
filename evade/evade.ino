#define DEBUGME

#include "Game.h"

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef SHOW_FPS
long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;
#endif

// Global variables.
Arduboy2Core arduboy;
BYTE game_mode = MODE_SPLASH;
BYTE app_settings = SETTINGS_AUDIO;

// using const saves RAM - we know what the frame rate is, so we may as well
// hard code it, saving the RAM in the process.
static const BYTE eachFrameMillis = 1000 / 30;
// We only need this one variable to track when to idle() while waiting for the
// next frame to start.
static ULONG nextFrameStart = 0;

static void initRandomSeed() {
  power_adc_enable(); // ADC on

  // do an ADC read from an unconnected input pin
  ADCSRA |= _BV(ADSC); // start conversion (ADMUX has been pre-set in boot())
  while (bit_is_set(ADCSRA, ADSC)) {
  } // wait for conversion complete

  randomSeed(((unsigned long)ADC << 16) + micros());

  power_adc_disable(); // ADC off
}

static BOOL pressed(UBYTE buttons) {
  return (arduboy.buttonsState() & buttons) == buttons;
}

static void flashlight() {
  if (!pressed(UP_BUTTON)) {
    return;
  }
  HighScore::reset();
  arduboy.sendLCDCommand(OLED_ALL_PIXELS_ON); // smaller than allPixelsOn()
  arduboy.digitalWriteRGB(RGB_ON, RGB_ON, RGB_ON);

  // prevent the bootloader magic number from being overwritten by timer 0
  // when a timer variable overlaps the magic number location, for when
  // flashlight mode is used for upload problem recovery
  power_timer0_disable();

  while (true) {
    arduboy.idle();
  }
}

void setup(void) {
  if (!HighScore::valid()) {
    HighScore::reset();
    app_settings = SETTINGS_AUDIO;
    HighScore::save_settings();
  }
#ifdef DEV
  HighScore::reset();
  app_settings = SETTINGS_AUDIO;
  HighScore::save_settings();
#endif

  // initiate arduboy instance
  arduboy.boot();
  flashlight();
  initRandomSeed();

  Sound::init();
  Graphics::fillScreen(BLACK);
  Starfield::init();
  ProcessManager::init();
  ObjectManager::init();

  ProcessManager::birth(Splash::entry, PTYPE_SYSTEM);
  nextFrameStart = millis();
}

void loop(void) {
  ULONG now = millis();
  // pause render until it's time for the next frame
  if (now < nextFrameStart) {
    arduboy.idle();
    return;
  }
  nextFrameStart = now + eachFrameMillis;

  Controls::run();
  Camera::move();
  if (game_mode == MODE_GAME) {
    Player::before_render();
  }
  Starfield::render();
  ProcessManager::run();
  ObjectManager::run();
  // process player bullets
  Bullet::run();
  EBullet::run();
  if (game_mode == MODE_GAME) {
// handle any player logic needed to be done after guts of game loop (e.g. render hud, etc.)
#ifdef ENABLE_LED
    LED::animate();
#endif
    Player::after_render();
  }
#ifdef SCORE_ENABLE
  if (game_mode != MODE_SPLASH && game_mode != MODE_HIGHSCORES) {
    Player::render_score();
  }
#else
  if (game_mode == MODE_GAMEOVER) {
    Player::render_score();
  }
#endif

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

  Font::printf(60, 5, "%d", fps);

#endif

// then we finaly we tell the arduboy to display what we just wrote to the
// display
// TODO instead of erasing the entire screen to black here, maybe we can erase the stars and lines
#if TRUE
  Graphics::display(TRUE);
#else
  Graphics::display();
  ObjectManager::erase();
#endif
}
