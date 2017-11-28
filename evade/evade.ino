#include "Game.h"

#define SHOW_FPS
//#undef SHOW_FPS

#ifdef SHOW_FPS
long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;
#endif

// Global variables.
Arduboy2Core arduboy;

BYTE frameCounter = 0;
static const BYTE eachFrameMillis = 1000 / 30;

ULONG nextFrameStart = 0;
Printer printer;

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
  // initiate arduboy instance
  arduboy.boot();
  flashlight();
  initRandomSeed();

  Sound::init();
  Graphics::fillScreen(BLACK);
  Starfield::init();
  ProcessManager::init();
  ObjectManager::init();

  ProcessManager::birth(Splash::splash_process, PTYPE_SYSTEM);
  //  ProcessManager::birth(player_process, PTYPE_SYSTEM);
  //  ProcessManager::birth(fighter1_process);

  Sound::play_score(DEMO_SCORE);
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

  frameCounter++;
  Controls::run();
  Camera::move();
  Starfield::render();
  ProcessManager::run();
  ObjectManager::run();

  // handle any player logic needed to be done after guts of game loop (e.g. render hud, etc.)
  Player::after_render();

  // TODO: remove this
  // to test BCD (it works)
  if ((frameCounter % 5) == 0) {
    Player::score = bcd_add(Player::score, 1);
  }
  if (Controls::pressed(B_BUTTON)) {
    char buf[9];
    bcd_string(Player::score, buf);
    printer.setCursor(64, 16);
    printer.setTextSize(1);
    printer.print(buf);
  }

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

  printer.setCursor(116, 4);
  printer.setTextSize(1);
  printer.print(fps);

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
