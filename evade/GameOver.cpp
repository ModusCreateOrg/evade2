#include "Game.h"

void GameOver::loop(Process *me) {
  Object *o = me->o;
  if (Controls::debounced(BUTTON_ANY)) {
    if (HighScore::isHighScore(Player::score) != -1) {
      ProcessManager::birth(HighScore::initials_process);
    }
    else {
      game_mode = MODE_SPLASH;
      ProcessManager::birth(Splash::splash_process);
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

void GameOver::process(Process *me) {
  game_mode = MODE_GAMEOVER;
  EBullet::genocide();
  Bullet::genocide();
  ProcessManager::genocide();

  Object *o = ObjectManager::alloc();
  me->o = o;
  o->x = 0;
  o->state = 0;
  Controls::reset();
  me->sleep(1, GameOver::loop);
}
