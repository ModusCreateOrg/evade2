#include "Evade2.h"

UBYTE Game::wave;
UBYTE Game::difficulty;
UBYTE Game::kills;

void Game::next_wave(Process *me, Object *o) {
  if (--Game::kills <= 0) {
    game_mode = MODE_GAME;
    Game::difficulty++;
    Game::kills = 0;
    Camera::vz = CAMERA_VZ;
    ProcessManager::genocide();
    ProcessManager::birth(Enemy::entry);
    ProcessManager::birth(Enemy::entry);
    ProcessManager::birth(Enemy::entry);
    me->suicide();
  }
  else {
    Font::printf(13, 20, "START WAVE %d", Game::wave);
    me->sleep(1);
  }
}

void Game::spawn_boss(Process *me, Object *o) {
  if (--Game::kills <= 0) {
    game_mode = MODE_GAME;
    Camera::vz = CAMERA_VZ;
    ProcessManager::genocide();
    ProcessManager::birth(Boss::entry);
    me->suicide();
  }
  else {
    Font::scale = 190;
    Font::printf(19, 20, "ACE APPROACHING!");
    Font::scale = 256;
    me->sleep(1);
  }
}

void Game::run() {
  if (Game::kills > 1) {
    game_mode = MODE_NEXT_WAVE;
    Game::wave++;
    // next wave
    Game::kills = 120;
    Camera::vz = 20;
    ProcessManager::birth(spawn_boss);
  }
}

struct game_data {
  FLOAT theta;
  WORD timer;
};

// Game process uses an Object that isn't displayed!
// The object structure provides some variable space we
// can use, saving precious global variable space.
void Game::start_game(Process *me) {
  // end wave after 180 seconds (3 minutes)
  Game::difficulty = 1;
  Game::kills = 0;
  Game::wave = 1;

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
