#define DEBUGME

#include "Evade2.h"

static const BYTE TYPEWRITER_SPEED = 3;
static const BYTE LINE_HEIGHT = 12;

static const char scout_text[] PROGMEM = "SCOUT: AGILE\nAND LETHAL!";
static const char bomber_text[] PROGMEM = "BOMBER: VERY\nAGGRESSIVE!";
static const char assault_text[] PROGMEM = "ASSAULT: WILL\nKILL YOU!";

static const char credits1[] PROGMEM = "CRAFTED BY\nMODUS CREATE\nDECEMBER 2017.\n\nHAPPY HOLIDAYS!";
static const char credits2[] PROGMEM = "DESIGN BY:\nJAY GARCIA";
static const char credits3[] PROGMEM = "MUSIC BY:\nJAY GARCIA\nDELIO BRIGNOLI";
static const char credits4[] PROGMEM = "ART BY:\nMICHAEL TINTIUC\nJAY GARCIA";
static const char credits5[] PROGMEM = "PROGRAMMING BY:\nJAY GARCIA\nDELIO BRIGNOLI\nMICHAEL TINTIUC\nMIKE SCHWARTZ";

const BYTE MAX_SCREEN = 2;
const BYTE MAX_CREDITS = 4;

struct attract_data {
  BYTE screen;
  BYTE y;
  BYTE offset;
  WORD timer;
  BOOL done;
  PGM_P text;
  BYTE enemy;
};

static void init_screen(attract_data *ad, BYTE y = 6) {
  if (game_mode == MODE_ATTRACT) {
    switch (ad->screen) {
      case 0:
        ad->enemy = ENEMY_SCOUT;
        ad->text = scout_text;
        y = 48;
        break;
      case 1:
        ad->enemy = ENEMY_BOMBER;
        ad->text = bomber_text;
        y = 48;
        break;
      case 2:
        ad->enemy = ENEMY_ASSAULT;
        ad->text = assault_text;
        y = 48;
        break;
    }
  }
  else {
    ad->enemy = -1;
    y = 6;
    switch (ad->screen) {
      case 0:
        ad->text = credits1;
        break;
      case 1:
        ad->text = credits2;
        break;
      case 2:
        ad->text = credits3;
        break;
      case 3:
        ad->text = credits4;
        break;
      case 4:
        ad->text = credits5;
        break;
    }
  }
  //  ad->len = strlen_P(text);
  ad->offset = 1;
  ad->y = y;
  ad->timer = TYPEWRITER_SPEED;
  ad->done = FALSE;
}

void Attract::next(Process *me, Object *o) {
  attract_data *ad = (attract_data *)&o->x;

  ad->timer--;
  if (ad->timer < 0) {
    ad->screen++;
    if ((game_mode == MODE_ATTRACT && ad->screen > MAX_SCREEN) || (game_mode == MODE_CREDITS && ad->screen > MAX_CREDITS)) {
      ProcessManager::birth(Splash::entry);
      me->suicide();
      return;
    }
    else {
      init_screen(ad);
      me->sleep(1, typewriter);
    }
  }
  else {
    me->sleep(1);
  }
}

void Attract::typewriter(Process *me, Object *o) {
  attract_data *ad = (attract_data *)&o->x;

  ad->timer--;

  if (Controls::debounced(BUTTON_A)) {
    ProcessManager::birth(Game::entry);
    me->suicide();
    return;
  }
  if (Controls::debounced(BUTTON_B)) {
    me->sleep(1, next);
    return;
  }

  if (ad->timer < 0) {
    if (ad->done) {
      ad->timer = 5;
      me->sleep(1, next);
      return;
    }
    ad->timer = TYPEWRITER_SPEED;
    ad->offset++;
  }

  if (ad->enemy != -1) {
    Graphics::drawVectorGraphic(Enemy::enemy_graphic(ad->enemy), 64.0, 16.0, 0.0, 2.0);
  }
  if (game_mode == MODE_CREDITS) {
    Font::scale = .8 * 256;
  }
  PGM_P p = ad->text;
  BYTE x = 6, y = ad->y;
  for (BYTE i = 0; i < ad->offset;) {
    char c = pgm_read_byte(p++);
    if (c == '\0') {
      if (!ad->done) {
        ad->timer = 60; // 2 seconds
        ad->done = TRUE;
      }
      break;
    }
    else if (c == '\n') {
      x = 6;
      y += LINE_HEIGHT;
    }
    else {
      x += Font::write(x, y, c);
      i++;
    }
  }
  if (game_mode == MODE_CREDITS) {
    Font::scale = 0x100;
  }
  me->sleep(1);
}

void Attract::entry(Process *me, Object *o) {
  attract_data *ad = (attract_data *)&o->x;
  ad->screen = 0;
  init_screen(ad);
  me->sleep(1, typewriter);
}
