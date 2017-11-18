#ifndef GAME_H
#define GAME_H

#include "Types.h"

const int NUM_STARS = 25;
const int NUM_OBJECTS = 4;
const int NUM_PROCESSES = 4;

const BYTE PTYPE_USER = 0;
const BYTE PTYPE_SYSTEM = 1;

class Starfield;
class Object;
class ObjectManager;
class Process;
class ProcessManager;

#include "Camera.h"
#include "Object.h"
#include "ObjectManager.h"
#include "Process.h"
#include "ProcessManager.h"
#include "Starfield.h"

#endif
