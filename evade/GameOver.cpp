#include "Game.h"

void GameOver::loop(Process *me, Object *o) {
  if (Controls::debounced(BUTTON_ANY)) {
    if (HighScore::isHighScore(Player::score) != -1) {
      ProcessManager::birth(HighScore::entry);
    }
    else {
      game_mode = MODE_SPLASH;
      ProcessManager::birth(Splash::entry);
    }
    me->suicide();
  }
  if (o->state & (1 << 4)) {
#ifdef ENABLE_LED
    LED::rgb(LED_BRIGHTNESS, 0, 0);
#endif
    //    Font::printf(30, 30, "GAME OVER");
  }
  Font::print_string_rotatedx(30, 30, o->x, F("GAME OVER"));
  o->x += 12;
#ifdef ENABLE_LED
  else {
    LED::rgb(0, 0, 0);
  }
#endif
  o->state++;
  me->sleep(1);
}

void GameOver::entry(Process *me) {
  Object *o = ObjectManager::alloc();
  me->o = o;

  game_mode = MODE_GAMEOVER;
  EBullet::genocide();
  Bullet::genocide();
  ProcessManager::genocide();

  o->x = 0;
  o->state = 0;
  Controls::reset();
  me->sleep(1, GameOver::loop);
  Sound::play_score(GAME_OVER_SONG);
}
