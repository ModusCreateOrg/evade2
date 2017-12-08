#define DEBUGME

#include "Game.h"

#include <EEPROM.h>
// some random address in EEPROM
#define ADDRESS 80

void HighScoreRecord::dump() {
  BYTE *src = (BYTE *)this;
  for (UBYTE i = 0; i < sizeof(HighScoreRecord); i++) {
    debug("%x ", *src++);
  }
  debug("\n");
}

void HighScore::save_settings() {
  EEPROM.write(ADDRESS + 6, app_settings);
}

BOOL HighScore::valid() {
  WORD addr = ADDRESS;
  if (EEPROM.read(addr) != 'E') {
    return FALSE;
  }
  if (EEPROM.read(++addr) != 'V') {
    return FALSE;
  }
  if (EEPROM.read(++addr) != 'A') {
    return FALSE;
  }
  if (EEPROM.read(++addr) != 'D') {
    return FALSE;
  }
  if (EEPROM.read(++addr) != 'E') {
    return FALSE;
  }
  if (EEPROM.read(++addr) != '2') {
    return FALSE;
  }
  // global settings byte
  app_settings = EEPROM.read(++addr);
  return TRUE;
}

BOOL HighScore::readRecord(BYTE index, HighScoreRecord *r) {
  if (!valid()) {
    reset();
  }
  if (index > HIGH_SCORE_RECORDS - 1) {
    return FALSE;
  }
  UBYTE *dst = (UBYTE *)r;
  WORD addr = ADDRESS + 7 + index * sizeof(HighScoreRecord);

  for (UBYTE i = 0; i < sizeof(HighScoreRecord); i++) {
    *dst++ = EEPROM.read(addr++);
  }
  return TRUE;
}

BOOL HighScore::writeRecord(BYTE index, HighScoreRecord *r) {
  if (index > HIGH_SCORE_RECORDS - 1) {
    return FALSE;
  }
  UBYTE *src = (UBYTE *)r;
  WORD addr = ADDRESS + 7 + index * sizeof(HighScoreRecord);

  for (UBYTE i = 0; i < sizeof(HighScoreRecord); i++) {
    EEPROM.write(addr++, *src++);
  }
  return TRUE;
}

BYTE HighScore::isHighScore(BCD score) {
  HighScoreRecord record;

  for (UBYTE index = 0; index < HIGH_SCORE_RECORDS; index++) {
    if (HighScore::readRecord(index, &record)) {
      if (record.score < score) {
        return index;
      }
    }
  }
  return -1;
}

void HighScore::reset() {
  static const PROGMEM char initials[] = {
    'J', 'G', ' ',
    'M', 'T', ' ',
    'M', 'Y', 'K',
    'L', 'E', 'D',
    'D', 'R', 'J',
  };

  HighScoreRecord record;
  const char *ps = initials;
  for (UBYTE index = 0; index < HIGH_SCORE_RECORDS; index++) {
    record.initials[0] = pgm_read_byte(ps++);
    record.initials[1] = pgm_read_byte(ps++);
    record.initials[2] = pgm_read_byte(ps++);
    record.score = 0;
    HighScore::writeRecord(index, &record);
  }
  WORD addr = ADDRESS;
  EEPROM.write(addr++, 'E');
  EEPROM.write(addr++, 'V');
  EEPROM.write(addr++, 'A');
  EEPROM.write(addr++, 'D');
  EEPROM.write(addr++, 'E');
  EEPROM.write(addr, '2');
}

void HighScore::renderHighScores() {
  HighScoreRecord record;
  char initials[4],
      score[9];

  initials[3] = '\0';

  Font::printf(20, 6, "HIGH SCORES");
  WORD y = 6 + 13;
  for (UBYTE index = 0; index < HIGH_SCORE_RECORDS; index++) {
    HighScore::readRecord(index, &record);
    initials[0] = record.initials[0];
    initials[1] = record.initials[1];
    initials[2] = record.initials[2];
    bcd_string(record.score, score);
    BYTE x = 20;
    Font::printf(x, y, "%d", index + 1);
    x += 12;
    Font::print_string(x, y, initials);
    x += 32;
    Font::print_string(x, y, &score[3]);
    y += 10;
  }
}

struct InitialsState {
  char initials[4];
  BYTE index;    // which character position
  BYTE timer;    // for repeat
  BYTE position; // which high score index
};

static void up(InitialsState *state) {
  char letter = state->initials[state->index];
  if (letter == 'Z') {
    letter = 'A';
  }
  else {
    letter++;
  }
  state->initials[state->index] = letter;
}

static void down(InitialsState *state) {
  char letter = state->initials[state->index];
  if (letter == 'A') {
    letter = 'Z';
  }
  else {
    letter--;
  }
  state->initials[state->index] = letter;
}

static void render_initials(InitialsState *state) {
  BYTE y = 20;
  Font::printf(12, y, "NEW HIGH SCORE!");
  y += 15;
  Font::printf(12, y, "ENTER INITIALS:");
  y += 15;
  // render initials
  const BYTE left = 48;
  BYTE x = left;
  Font::write(x, y, state->initials[0]);
  x += 10;
  Font::write(x, y, state->initials[1]);
  x += 10;
  Font::write(x, y, state->initials[2]);
  y += 9;
  // underline the active letter
  x = left + state->index * 10 + -4;
  Graphics::drawLine(x, y, x + 8, y);
}

void HighScore::loop(Process *me, Object *o) {
  InitialsState *state = (InitialsState *)&o->x;

  if (Controls::debounced(BUTTON_A)) {
    HighScoreRecord r;

    // move all the records in EEPROM down one, to make a spot
    // for the new high score record
    for (BYTE i = HIGH_SCORE_RECORDS - 1; i > state->position; i--) {
      HighScore::readRecord(i - 1, &r);
      HighScore::writeRecord(i, &r);
    }

    // write the new high score record
    r.initials[0] = state->initials[0];
    r.initials[1] = state->initials[1];
    r.initials[2] = state->initials[2];
    r.score = Player::score;
    HighScore::writeRecord(state->position, &r);

    game_mode = MODE_HIGHSCORES;
    ProcessManager::birth(Splash::entry);
    me->suicide();
    return;
  }
  if (Controls::debounced(JOYSTICK_UP)) {
    up(state);
    state->timer = 20;
  }
  else if (Controls::debounced(JOYSTICK_DOWN)) {
    down(state);
    state->timer = 20;
  }
  else if (Controls::debounced(JOYSTICK_LEFT)) {
    state->index--;
    if (state->index < 0) {
      state->index = 2;
    }
  }
  else if (Controls::debounced(JOYSTICK_RIGHT)) {
    state->index++;
    if (state->index > 2) {
      state->index = 0;
    }
  }
  else {
    state->timer--;
    if (state->timer <= 0) {
      if (Controls::pressed(JOYSTICK_UP)) {
        up(state);
      }
      else if (Controls::pressed(JOYSTICK_DOWN)) {
        down(state);
      }
    }
  }
  render_initials(state);
  me->sleep(1);
}

void HighScore::entry(Process *me, Object *o) {
  o = ObjectManager::alloc();
  me->o = o;

  InitialsState *state = (InitialsState *)&o->x;
  state->position = HighScore::isHighScore(Player::score);
  state->initials[0] = state->initials[1] = state->initials[2] = 'A';
  state->initials[3] = '\0';
  state->index = 0;
  state->timer = 20;
  me->sleep(1, loop);
}
