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
WORD frameCount = -1;
UBYTE eachFrameMillis;
unsigned long lastFrameStart;
unsigned long nextFrameStart = 0;
bool justRendered = false;
uint8_t lastFrameDurationMs;
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
static void setFrameRate(uint8_t rate) {
  eachFrameMillis = 1000 / rate;
}

static bool everyXFrames(uint8_t frames) {
  return frameCount % frames == 0;
}

static bool nextFrame() {
  unsigned long now = millis();
  bool tooSoonForNextFrame = now < nextFrameStart;

  if (justRendered) {
    lastFrameDurationMs = now - lastFrameStart;
    justRendered = false;
    return false;
  }
  else if (tooSoonForNextFrame) {
    // if we have MORE than 1ms to spare (hence our comparison with 2),
    // lets sleep for power savings.  We don't compare against 1 to avoid
    // potential rounding errors - say we're actually 0.5 ms away, but a 1
    // is returned if we go to sleep we might sleep a full 1ms and then
    // we'd be running the frame slighly late.  So the last 1ms we stay
    // awake for perfect timing.

    // This is likely trading power savings for absolute timing precision
    // and the power savings might be the better goal. At 60 FPS trusting
    // chance here might actually achieve a "truer" 60 FPS than the 16ms
    // frame duration we get due to integer math.

    // We should be woken up by timer0 every 1ms, so it's ok to sleep.
    if ((uint8_t)(nextFrameStart - now) >= 2)
      arduboy.idle();

    return false;
  }

  // pre-render
  justRendered = true;
  lastFrameStart = now;
  nextFrameStart = now + eachFrameMillis;
  frameCount++;

  return true;
}

void setup(void) {
  // initiate arduboy instance
  arduboy.boot();
  flashlight();
  initRandomSeed();
  setFrameRate(FRAMERATE);

  Sound::init();
  Graphics::fillScreen(BLACK);
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
  if (!(nextFrame()))
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
