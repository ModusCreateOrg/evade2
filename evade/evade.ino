
#include "Star.h"
#include <Arduboy2.h>

#define SCREEN_WIDTH WIDTH   // Screen width in pixels.
#define SCREEN_HEIGHT HEIGHT // Screen height in pixels.

// Program constants.
#define STAR_COUNT                                                             \
  15 // Number of stars on the screen. Arduino UNO maxes out around 250.
#define BACKGROUND_COLOR BLACK // Background color in hex. 0x0000 is black.
#define STAR_SPEED_MIN                                                         \
  1 // Minimum movement in pixels per update. (value is inclusive)
#define STAR_SPEED_MAX                                                         \
  50 // Maximum movement in pixels per update. (value is inclusive)
#define STAR_COLOR WHITE // Star color in hex. 0xffff is white.
#define SHOW_FPS

#ifdef SHOW_FPS

long previousTime = 0;
uint8_t fps = 0, fpsCounter = 0;

#endif

// Global variables.
Star stars[STAR_COUNT]; // An array of star instances.
float travelx = 0;
float travely = 0;
int screenState = 0; // the state the game is in
bool faster;
bool slower;
int curSpeed = 5;
int minSpeed = 1;
long actualTime = 0;
long speedMills;
int starCount = STAR_COUNT;

// player variables
float shipX = 0;
float shipY = 0;
float shipZ = 0;
float shipHeading = 0;

const int maxMapX = 1000;
const int minMapX = -1000;
const int maxMapY = 1000;
const int minMapY = -1000;
const int maxMapZ = 1000;
const int minMapZ = -1000;

Arduboy2 arduboy;

/**
   Prepare the stars for their first display.
*/
void starsSetup() {
  // Loop through each star.
  for (int i = 0; i < STAR_COUNT; i++) {
    // Randomize its position and speed.
    stars[i].randomize(-1000, 1000, -1000, 1000, 100, 1000, STAR_SPEED_MIN,
                       STAR_SPEED_MAX);
  }
}

/**
   Prepare the screen for displaying.
*/
void screenSetup() {

  arduboy.setFrameRate(60);
  arduboy.clear();
}

void setup(void) {
  // initiate arduboy instance
  arduboy.boot();
  screenSetup();
  starsSetup();
  // arduboy.initRandomSeed();
}

void handleButtons() {
  arduboy.pollButtons();
  if (arduboy.pressed(UP_BUTTON) == true) {
    travely = 0.03;
  }

  if (arduboy.pressed(DOWN_BUTTON) == true) {
    travely = -0.03;
  }

  if (arduboy.pressed(LEFT_BUTTON) == true)
    travelx = -0.03;
  if (arduboy.pressed(RIGHT_BUTTON) == true)
    travelx = 0.03;
  if (arduboy.justPressed(A_BUTTON) == true) {
    faster = true;
  }
  if (arduboy.justReleased(A_BUTTON) == true) {
    faster = false;
  }
  if (arduboy.justPressed(B_BUTTON) == true) {
    slower = true;
  }
  if (arduboy.justReleased(B_BUTTON) == true) {
    slower = false;
  }
  if (arduboy.pressed(A_BUTTON + B_BUTTON) && arduboy.justPressed(UP_BUTTON)) {
    travelx = 0;
  }
  if (arduboy.pressed(A_BUTTON + B_BUTTON) &&
      arduboy.justPressed(DOWN_BUTTON)) {
    travely = 0;
  }
  if (arduboy.justReleased(UP_BUTTON) == true) {
    travely = 0;
  }
  if (arduboy.justReleased(DOWN_BUTTON) == true) {
    travely = 0;
  }
  if (arduboy.justReleased(LEFT_BUTTON) == true) {
    travelx = 0;
  }
  if (arduboy.justReleased(RIGHT_BUTTON) == true) {
    travelx = 0;
  }
}

void loop(void) {
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;
  switch (screenState) {
    case 0:
      arduboy.clear();
      arduboy.setCursor(20, 10);
      arduboy.print("3D Starfield Test");
      arduboy.setCursor(21, 20);
      arduboy.print("By: Justin");
      arduboy.setCursor(50, 30);
      arduboy.print("Presler");
      arduboy.setCursor(20, HEIGHT - 20);
      if (millis() % 2000 < 1000) {
        arduboy.print("Press A Button");
      }
      else
        arduboy.print("Press   Button");
      if (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON) == true) {
        arduboy.initRandomSeed();
        screenState = 1;
      }
      break;
    case 1:
      arduboy.clear();
      handleButtons();
      starsDraw(travelx, travely);
      arduboy.setCursor(WIDTH / 2 - 10, HEIGHT - 7);
      arduboy.print("SPEED: ");
      arduboy.print(curSpeed);

#ifdef SHOW_FPS
      fpsCounter++;
      actualTime = millis();
      if ((fpsCounter % 30) == 0) {
        if (previousTime != 0) {
          fps = (30 * 1000 / (actualTime - previousTime));
        }
        previousTime = actualTime;
        fpsCounter = 0;
      }

      arduboy.setCursor(116, 4);
      arduboy.print(fps);

#endif

      break;
    default:
      // statements
      break;
  }

  // then we finaly we tell the arduboy to display what we just wrote to the
  // display
  arduboy.display();
}

/**
   Update the positions of the stars and redraw them on the screen.
*/
void starsDraw(float travelx, float travely) {
  // Loop through each star.
  for (int i = 0; i < starCount; i++) {
    stars[i].z = stars[i].z - curSpeed;

    if (travely != 0) {
      float temp_y = stars[i].y;
      float temp_z = stars[i].z;
      float cos_y = cos(travely);
      float sin_y = sin(travely);
      stars[i].y = temp_y * cos_y - temp_z * sin_y;
      stars[i].z = temp_z * cos_y + temp_y * sin_y;
      //      float temp_y = stars[i].y;
      //      float temp_z = stars[i].z;
      //      stars[i].y = temp_y * cos(travely) - temp_z * sin(travely);
      //      stars[i].z = temp_z * cos(travely) + temp_y * sin(travely);
    }
    if (travelx != 0) {
      float temp_x = stars[i].x;
      float temp_z = stars[i].z;
      float cos_y = cos(travelx);
      float sin_y = sin(travelx);
      stars[i].x = temp_x * cos_y - temp_z * sin_y;
      stars[i].z = temp_z * cos_y + temp_x * sin_y;
      //      float temp_x = stars[i].x;
      //      float temp_y = stars[i].y;
      //      stars[i].x = temp_x * cos(travelx) - temp_y * sin(travelx);
      //      stars[i].y = temp_y * cos(travelx) + temp_x * sin(travelx);
    }
    // caclulate screen position from 3D space
    stars[i].screen_x = stars[i].x / stars[i].z * 100 + WIDTH / 2;
    stars[i].screen_y = stars[i].y / stars[i].z * 100 + HEIGHT / 2;

    actualTime = millis();
    if (faster == true && slower == false && curSpeed < STAR_SPEED_MAX &&
        actualTime - speedMills >= 100) {
      curSpeed = curSpeed + 1;
      minSpeed = STAR_SPEED_MIN;
      speedMills = actualTime;
    }
    if (slower == true && faster == false && curSpeed != STAR_SPEED_MIN &&
        actualTime - speedMills >= 100) {
      curSpeed = curSpeed - 1;
      minSpeed = STAR_SPEED_MIN;
      speedMills = actualTime;
    }

    // If the stars go off the screen remove them and re-draw. if the stars hang
    // out in the center remove them also
    if (stars[i].screen_x > WIDTH || stars[i].screen_x < 0 ||
        stars[i].screen_y > HEIGHT || stars[i].screen_y < 0 ||
        (stars[i].screen_x == WIDTH / 2 && stars[i].screen_y == HEIGHT / 2)) {
      stars[i].randomize(-500, 1000, -500, 1000, 100, 2000, STAR_SPEED_MIN,
                         STAR_SPEED_MAX);

      stars[i].screen_x = stars[i].x / stars[i].z * 100 + WIDTH / 2;
      stars[i].screen_y = stars[i].y / stars[i].z * 100 + HEIGHT / 2;
      stars[i].old_screen_x = stars[i].screen_x;
      stars[i].old_screen_y = stars[i].screen_y;
    }
    // Draw the star at its new coordinate.
    arduboy.drawLine(stars[i].screen_x, stars[i].screen_y,
                     stars[i].old_screen_x, stars[i].old_screen_y, STAR_COLOR);

    // keep track of the old spot
    stars[i].old_screen_x = stars[i].screen_x;
    stars[i].old_screen_y = stars[i].screen_y;
  }
}
