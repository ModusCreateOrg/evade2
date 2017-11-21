#ifndef GAME_H
#define GAME_H

#define DEV
//#undef DEV

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

const int NUM_OBJECTS = 8;
const int NUM_PROCESSES = 8;

// we should probably key on FRAMERATE and adjust things accordingly
const int FRAMERATE = 30;
const int NUM_STARS = 25;

// joystick up/down/left/right changes camera by DELTACONTROL
const float DELTACONTROL = 11;
// speed of camera flying through stars
const float CAMERA_VZ = 6;
// speed of player bullets
const float BULLET_VZ = 14;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

// Todo change to <ATMLib.h> once we publish
#include "src/ATMLib2/ATMlib.h"
#include "sound/song.h"

extern Arduboy2 arduboy;
extern Starfield starfield;
extern Controls controls;

#include "Camera.h"
#include "Controls.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Starfield.h"
#include "debug.h"

#include "Bullet.h"
#include "Fighter1.h"

#endif
