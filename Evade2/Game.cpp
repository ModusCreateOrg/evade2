#include "Evade2.h"

UBYTE Game::wave;
UBYTE Game::difficulty;
UBYTE Game::kills;

const BYTE alert_top = 5;

const BYTE getStageSong() {
  if (Game::wave % 5 == 0) {
    return STAGE_5_SONG;
  }
  else if (Game::wave % 4 == 0) {
    return STAGE_4_SONG;
  }
  else if (Game::wave % 3 == 0) {
    return STAGE_3_SONG;
  }
  else if (Game::wave % 2 == 0) {
    return STAGE_2_SONG;
  }
  return STAGE_1_SONG;
}

void Game::birth() {
  EBullet::genocide();
  Bullet::genocide();
  ProcessManager::genocide();

  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);
  ProcessManager::birth(Enemy::entry);

  if (Game::wave > 3) {
    const BYTE num_asteroids = min(max(Game::wave, 3), 1) + 1;
    for (BYTE i = 0; i < num_asteroids; i++) {
      ProcessManager::birth(Asteroid::entry);
    }  
  } 
}

void Game::next_wave(Process *me, Object *o) {
  if (--Game::kills <= 0) {
    game_mode = MODE_GAME;
    Game::kills = 0;
    Camera::vz = CAMERA_VZ;
    Game::wave++; // <-- Use this with Kills

    if (Game::wave % 4 == 0) {
      Game::difficulty++;
    }
    Sound::play_score(getStageSong());

    EBullet::genocide();
    Bullet::genocide();
    ProcessManager::genocide();

    // birth enemies, etc.
    Game::birth();
    me->suicide();
  }
  else {
    Font::scale = 200;
    Font::printf(26, alert_top, "START WAVE %d", Game::wave + 1);
    Font::scale = 256;
    Player::recharge_shield();
    Player::recharge_power();
    me->sleep(1);
  }
}

// Using game::kills as a timer
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
    Font::printf(35, alert_top, "WARP TO ACE!");
    Player::recharge_shield();
    Player::recharge_power();
    Font::scale = 256;
    me->sleep(1);
  }
}

// TOOD: Make subroutine to map out wave to kills

void Game::run() {
  // if (Game::kills > 0) { // <<-- use this one to debug quickly
  // Faster increase
  // if (Game::kills > (4 * Game::wave) * Game::difficulty) {

  // Slower increase
  if (Game::kills > ((10 + Game::wave) * Game::difficulty)) {

    game_mode = MODE_NEXT_WAVE;
    // next wave
    Game::kills = 120;
    Camera::vz = 30;
    Bullet::genocide();
    ProcessManager::birth(spawn_boss);
    Sound::play_score(GET_READY_SONG);
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
  Sound::play_score(getStageSong());
  Player::init();
  Game::birth();
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
  d->timer = 65;
  d->theta = 90;
  Sound::play_score(NEXT_WAVE_SONG);
  me->sleep(1, get_ready);
}
