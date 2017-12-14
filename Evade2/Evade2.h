#ifndef EVADE2_H
#define EVADE2_H

#define DEV
#undef DEV

#define INIT_SERIAL
#undef INIT_SERIAL

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

// if not defined, only the characters we use will be included
// affects Font class and charset.h
#define FULL_CHARSET
#undef FULL_CHARSET

// define this to allow printing of floats with our custom font:

#define PRINTF_FLOAT
#undef PRINTF_FLOAT

// define this to enable audio
#define ENABLE_AUDIO
#undef ENABLE_AUDIO

// define this to enable HUD movements when you fly around
#define ENABLE_HUD_MOVEMENTS
// #undef ENABLE_HUD_MOVEMENTS

// Modus Create LOGO splash screen first time
#define ENABLE_MODUS_LOGO
//#undef ENABLE_MODUS_LOGO

// If FAST_LINE_ENABLE is set, the fast line drawing algorithm is used
// While it is a bit faster, it seems to have some rounding errors that
// render lines not 100% correct.
//
// if not defined, the bresnehan line drawing algorithm from arduboy2 is used.
#define FAST_LINE_ENABLE
#undef FAST_LINE_ENABLE

// if SCORE_ENABLE is defined, the score will be displayed on
// screen during game play.
#define SCORE_ENABLE
#undef SCORE_ENABLE

// if ENABLE_ROTATING_TEXT is defined, the game will rotate some text
// around x, which is nice eye candy.  If not defined, there should be
// less FLASH used.
#define ENABLE_ROTATING_TEXT
//#undef ENABLE_ROTATING_TEXT

// const variables take NO RAM, they are like #define, but with type info for the
// compiler to use when checking validity of code.

const int FRAMERATE = 30;

const int NUM_OBJECTS = 12;
const int NUM_PROCESSES = 5;

// we should probably key on FRAMERATE and adjust things accordingly
const int NUM_STARS = 5;

// joystick up/down/left/right changes camera by DELTACONTROL
const float DELTACONTROL = 11;
// speed of camera flying through stars
const float CAMERA_VZ = 6;
// speed of player bullets
const float BULLET_VZ = 15;

const BYTE MAX_BULLETS = 6;

// Used for enemies and bosses
#define BANK_LEFT (1 << OFLAG_USER_BIT)
#define ORBIT_LEFT (1 << (OFLAG_USER_BIT + 1))

class Sound;
class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

extern Arduboy2Core arduboy;

#define MODE_LOGO 0
#define MODE_SPLASH 1
#define MODE_ATTRACT 2
#define MODE_CREDITS 3
#define MODE_GAME 4
#define MODE_NEXT_WAVE 5
#define MODE_GAMEOVER 6

extern UBYTE game_mode;

#include "Controls.h"
#include "Font.h"
#include "Graphics.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Sound.h"
#include "debug.h"

#include "Attract.h"
#include "Game.h"
#include "GameOver.h"
#include "Logo.h"
#include "Splash.h"

#include "Boss.h"
#include "Bullet.h"
#include "Camera.h"
#include "EBullet.h"
#include "Enemy.h"

#include "Player.h"
#include "Starfield.h"

#endif
