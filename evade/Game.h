#ifndef GAME_H
#define GAME_H

#define DEV
//#undef DEV

#include "Types.h"

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

const int NUM_STARS = 20;
const int NUM_OBJECTS = 8;
const int NUM_PROCESSES = 8;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Controls;
class Object;
class ObjectManager;
class Process;
class ProcessManager;
class Starfield;

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
#include "Enemy1.h"

#endif
