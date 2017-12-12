#include "Evade2.h"

UBYTE Game::difficulty = 3;

struct game_data {
  FLOAT theta;
  WORD timer;
};

// Game process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Game::start_game(Process *me) {
  game_mode = MODE_GAME;
  Sound::stfu();
  Sound::play_score(STAGE_1_SONG);
  Player::init();
  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);
  //  ProcessManager::birth(Enemy_Scout::enemy_scout_process);
  //  ProcessManager::birth(Enemy_Heavy_Bomber::enemy_heavy_bomber_process);
  me->suicide();
}

/**
 * Display "Get Ready" for o->state frames
 */
void Game::get_ready(Process *me, Object *o) {
  game_data *d = (game_data *)&o->x;

#ifdef ENABLE_ROTATING_TEXT
  Font::print_string_rotatedx(30, 35, d->theta, F("GET READY!"));
  d->theta += 12;
#else
  Font::printf(30, 35, "GET READY!");
#endif
  BYTE timer = d->timer;

  if (timer <= 1) {
    Game::start_game(me);
    return;
  }
  d->timer--;
  me->sleep(1);
}

void Game::entry(Process *me, Object *o) {
  game_data *d = (game_data *)&o->x;
  d->timer = 60;
  d->theta = 90;
  Sound::play_score(GET_READY_SONG);
  me->sleep(1, get_ready);
}
