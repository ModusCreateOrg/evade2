#include "Evade2.h"

void GameOver::loop(Process *me, Object *o) {
  if (--o->timer < -0) {
    ProcessManager::birth(Splash::entry);
    me->suicide();
  }
#ifdef ENABLE_ROTATING_TEXT
  o->theta += 12;
  Font::print_string_rotatedx(30, 20, o->theta, F("GAME OVER"));
  Font::scale = .75 * 256;
  Font::printf(Game::wave < 9 ? 18 : 13, 45, "WAVES SURVIVED: %d", Game::wave - 1);
  Font::scale = 256;
#else
  Font::printf(30, 30, "GAME OVER");
#endif
  o->state++;
  me->sleep(1);
}

void GameOver::entry(Process *me, Object *o) {
  EBullet::genocide();
  Bullet::genocide();
  ProcessManager::genocide();

  game_mode = MODE_GAMEOVER;
#ifdef ENABLE_ROTATING_TEXT
  o->theta = 0;
#endif
  o->state = 0;
  o->timer = 100;
  Controls::reset();
  me->sleep(1, GameOver::loop);
  arduboy.invert(FALSE);
  Sound::play_score(GAME_OVER_SONG);
}
