#ifndef SONG_H
#define SONG_H

#include "atm_cmd_constants.h"

#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))

const PROGMEM struct score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[8];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t pattern0[5];
  uint8_t pattern1[6];
  uint8_t pattern2[5];
  uint8_t pattern3[7];
  uint8_t pattern4[21];
  uint8_t pattern5[18];
  uint8_t pattern6[13];
  uint8_t pattern7[22];
} score = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct score_data),
  .patterns_offset = {
      offsetof(struct score_data, pattern0),
      offsetof(struct score_data, pattern1),
      offsetof(struct score_data, pattern2),
      offsetof(struct score_data, pattern3),
      offsetof(struct score_data, pattern4),
      offsetof(struct score_data, pattern5),
      offsetof(struct score_data, pattern6),
      offsetof(struct score_data, pattern7),
  },
  .num_channels = 4,
  .start_patterns = {
    0x02,                         // Channel 0 entry track (PULSE)
    0x01,                         // Channel 1 entry track (SQUARE)
    0x00,                         // Channel 2 entry track (TRIANGLE)
    0x03,                         // Channel 3 entry track (NOISE)
  },
  .pattern0 = {
    //"Track 0"                   // ticks = 64 / bytes = 4
    ATM_CMD_M_SET_VOLUME(0),
    ATM_CMD_M_DELAY_TICKS(32),
    ATM_CMD_M_DELAY_TICKS(32),
    ATM_CMD_I_STOP,
  },
  .pattern1 = {
    //"Track 1"                   // ticks = 2048 / bytes = 6
    ATM_CMD_M_SET_TEMPO(50),
    ATM_CMD_M_CALL_REPEAT(4, 4),
    ATM_CMD_I_STOP,
  },
  .pattern2 = {
    //"Track 2"                   // ticks = 2048 / bytes = 5
    ATM_CMD_M_CALL_REPEAT(6, 32),
    ATM_CMD_I_NOTE_OFF,
    ATM_CMD_I_STOP,
  },
  .pattern3 = {
    //"Track 3"                   // ticks = 2048 / bytes = 7
    ATM_CMD_M_CALL_REPEAT(0, 8),
    ATM_CMD_M_CALL_REPEAT(7, 24),
    ATM_CMD_I_STOP,
  },
  .pattern4 = {
    //"Track 4"                   // ticks = 512 / bytes = 21
    ATM_CMD_M_CALL_REPEAT(5, 2),
    ATM_CMD_M_ADD_TRANSPOSITION(3),
    ATM_CMD_M_CALL_REPEAT(5, 2),
    ATM_CMD_M_ADD_TRANSPOSITION(-1),
    ATM_CMD_M_CALL_REPEAT(5, 2),
    ATM_CMD_M_ADD_TRANSPOSITION(3),
    ATM_CMD_M_CALL_REPEAT(5, 2),
    ATM_CMD_M_ADD_TRANSPOSITION(-5),
    ATM_CMD_I_RETURN,
  },
  .pattern5 = {
    //"Track 5"                   // ticks = 64 / bytes = 14
    ATM_CMD_I_NOTE_B5,
    ATM_CMD_M_SET_VOLUME(63),
    ATM_CMD_M_SLIDE_VOL_ON(-16),
    ATM_CMD_M_DELAY_TICKS(16),
    ATM_CMD_M_SET_VOLUME(16),
    ATM_CMD_M_SLIDE_VOL_ON(-4),
    ATM_CMD_M_DELAY_TICKS(4),
    ATM_CMD_M_SLIDE_VOL_OFF,
    ATM_CMD_M_DELAY_TICKS(20),
    ATM_CMD_M_DELAY_TICKS(24),
    ATM_CMD_I_RETURN,
  },
  .pattern6 = {
    //"track 6"                   // ticks = 64 / bytes = 10
    ATM_CMD_I_NOTE_B2,
    ATM_CMD_M_SET_VOLUME(32),
    ATM_CMD_M_TREMOLO_ON(1, 30),
    ATM_CMD_M_DELAY_TICKS(32),
    ATM_CMD_M_DELAY_TICKS(31),
    ATM_CMD_M_TREMOLO_OFF,
    ATM_CMD_M_DELAY_TICKS(3),
    ATM_CMD_I_RETURN,
  },
  .pattern7 = {
    //"track 7"                   // ticks = 64 / bytes = 20
    ATM_CMD_M_SET_VOLUME(32),
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_M_SET_VOLUME(0),
    ATM_CMD_M_DELAY_TICKS(16),

    ATM_CMD_M_SET_VOLUME(32),
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_M_SET_VOLUME(0),
    ATM_CMD_M_DELAY_TICKS(16),
  
    ATM_CMD_M_SET_VOLUME(32),
    ATM_CMD_M_SLIDE_VOL_ON(-2),
    ATM_CMD_M_DELAY_TICKS(17),
    ATM_CMD_M_SLIDE_VOL_OFF,
    ATM_CMD_M_DELAY_TICKS(17),
    ATM_CMD_I_RETURN,
  },
};

const PROGMEM struct sfx1_data {
  uint8_t fmt;
  uint8_t pattern0[9];
} pew = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(22),
    ATM_CMD_M_SET_VOLUME(63),
    ATM_CMD_I_NOTE_C3,
    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_NOTE_OFF,
    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_STOP,
  },
};

#endif

