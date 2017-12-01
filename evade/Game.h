#ifndef GAME_H
#define GAME_H

#define DEV
#undef DEV

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

// define this to enable LED logic
// note: this seems to take 20 bytes of RAM!
#define ENABLE_LED_LOGIC
#undef ENABLE_LED_LOGIC

// define this to enable audio
#define ENABLE_AUDIO
//#undef ENABLE_AUDIO

// if SMART_ERASE is defined, the engine will try to erase
// all the lines and points drawn previous frame instead
// of clearing the whole screen to black each frame.
#define SMART_ERASE
#undef SMART_ERASE

// const variables take NO RAM, they are like #define, but with type info for the
// compiler to use when checking validity of code.

const int FRAMERATE = 30;

const int NUM_OBJECTS = 10;
const int NUM_PROCESSES = 12;

// we should probably key on FRAMERATE and adjust things accordingly
const int NUM_STARS = 15;

// joystick up/down/left/right changes camera by DELTACONTROL
const float DELTACONTROL = 11;
// speed of camera flying through stars
const float CAMERA_VZ = 6;
// speed of player bullets
const float BULLET_VZ = 21;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Sound;
class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

extern Arduboy2Core arduboy;
extern BYTE frameCounter;

#include "Camera.h"
#include "Controls.h"
#include "Font.h"
#include "Graphics.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Sound.h"
#include "Starfield.h"
#include "debug.h"

#include "Splash.h"

#include "Bullet.h"
#include "Fighter1.h"
#include "Player.h"

#define TX_LED_ON() PORTD &= ~(1 << 5)
#define TX_LED_OFF() PORTD |= (1 << 5)
#define RX_LED_ON() PORTB &= ~(1 << 0)
#define RX_LED_OFF() PORTB |= (1 << 0)
#define L_LED_ON() PORTC &= ~(1 << 7)
#define L_LED_OFF() PORTC |= (1 << 7)
#endif
