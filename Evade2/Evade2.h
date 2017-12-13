#ifndef EVADE2_H
#define EVADE2_H

#define DEV
#undef DEV

#ifdef DEV
#define INIT_SERIAL
#endif

#define INIT_SERIAL
#undef INIT_SERIAL

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

// define this to enable audio
#define ENABLE_AUDIO
// #undef ENABLE_AUDIO

// define this to enable HUD movements when you fly around
#define ENABLE_HUD_MOVEMENTS
// #undef ENABLE_HUD_MOVEMENTS

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
// 11 - 14
const float DELTACONTROL = 11;

// speed of camera flying through stars
const float CAMERA_VZ = 6;
// speed of player bullets
const float BULLET_VZ = 15; // BULLET_VZ + CAMERA_VZ is the real speed

const BYTE MAX_BULLETS = 6;

class Sound;
class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

extern Arduboy2Core arduboy;

#define MODE_SPLASH 1
#define MODE_ATTRACT 2
#define MODE_GAME 3
#define MODE_NEXT_WAVE 4
#define MODE_ACE 5
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

#include "Camera.h"
#include "Starfield.h"

#include "Attract.h"
#include "Game.h"
#include "GameOver.h"
#include "Splash.h"

#include "Boss.h"
#include "Bullet.h"
#include "EBullet.h"
#include "Enemy.h"
#include "Player.h"

#endif
