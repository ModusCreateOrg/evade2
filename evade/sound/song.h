#ifndef SONG_H
#define SONG_H

//TODO: use <atm_cmd_constants.h> once we publish ATMLib2
#include "../src/ATMLib2/atm_cmd_constants.h"


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif

#ifndef NUM_PATTERNS
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))
#endif

#ifndef DEFINE_PATTERN
#define DEFINE_PATTERN(pattern_id, values) const uint8_t pattern_id[] = values;
#endif
  
/* pattern (channel) / bytes = 39*/
#define pattern0_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_SET_TEMPO(22), \
    ATM_CMD_M_CALL_REPEAT(6, 3), \
    ATM_CMD_M_CALL(7), \
    ATM_CMD_M_CALL_REPEAT(6, 3), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(12), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(13), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(pattern0_array, pattern0_data);
    
/* pattern (channel) / bytes = 27*/
#define pattern1_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_CALL_REPEAT(14, 12), \
    ATM_CMD_M_CALL_REPEAT(15, 4), \
    ATM_CMD_M_CALL_REPEAT(14, 12), \
    ATM_CMD_M_CALL_REPEAT(16, 4), \
    ATM_CMD_M_CALL_REPEAT(14, 10), \
    ATM_CMD_M_CALL_REPEAT(15, 2), \
    ATM_CMD_M_CALL_REPEAT(14, 10), \
    ATM_CMD_M_CALL_REPEAT(16, 2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(pattern1_array, pattern1_data);
    
/* pattern (channel) / bytes = 1*/
#define pattern2_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(pattern2_array, pattern2_data);
    
/* pattern (channel) / bytes = 13*/
#define pattern3_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_CALL_REPEAT(9, 7), \
    ATM_CMD_M_CALL(17), \
    ATM_CMD_M_CALL_REPEAT(18, 11), \
    ATM_CMD_M_CALL(19), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(pattern3_array, pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define pattern4_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern4_array, pattern4_data);
    
/* pattern (drum) / bytes = 7*/
#define pattern5_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_SLIDE_VOL_ON(-16), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_SLIDE_VOL_OFF, \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern5_array, pattern5_data);
    
/* pattern (tune) / "ld 1" / bytes = 17*/
#define pattern6_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern6_array, pattern6_data);
    
/* pattern (tune) / "ld 2" / bytes = 9*/
#define pattern7_data { \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(12), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern7_array, pattern7_data);
    
/* pattern (tune) / "ld 3" / bytes = 9*/
#define pattern8_data { \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(11), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern8_array, pattern8_data);
    
/* pattern (tune) / "perc" / bytes = 19*/
#define pattern9_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern9_array, pattern9_data);
    
/* pattern (tune) / "ld 4" / bytes = 9*/
#define pattern10_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern10_array, pattern10_data);
    
/* pattern (tune) / "LD 5" / bytes = 9*/
#define pattern11_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern11_array, pattern11_data);
    
/* pattern (tune) / "ld 6" / bytes = 13*/
#define pattern12_data { \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern12_array, pattern12_data);
    
/* pattern (tune) / "LD 8" / bytes = 13*/
#define pattern13_data { \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern13_array, pattern13_data);
    
/* pattern (tune) / "Bass C" / bytes = 17*/
#define pattern14_data { \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern14_array, pattern14_data);
    
/* pattern (tune) / "BASS A#" / bytes = 17*/
#define pattern15_data { \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern15_array, pattern15_data);
    
/* pattern (tune) / "BASS D" / bytes = 15*/
#define pattern16_data { \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern16_array, pattern16_data);
    
/* pattern (tune) / "PERC2" / bytes = 34*/
#define pattern17_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern17_array, pattern17_data);
    
/* pattern (tune) / "PERC3" / bytes = 13*/
#define pattern18_data { \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern18_array, pattern18_data);
    
/* pattern (tune) / "PERC 4" / bytes = 20*/
#define pattern19_data { \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(pattern19_array, pattern19_data);
    
const PROGMEM struct score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[20];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t pattern0[sizeof(pattern0_array)];
  uint8_t pattern1[sizeof(pattern1_array)];
  uint8_t pattern2[sizeof(pattern2_array)];
  uint8_t pattern3[sizeof(pattern3_array)];
  uint8_t pattern4[sizeof(pattern4_array)];
  uint8_t pattern5[sizeof(pattern5_array)];
  uint8_t pattern6[sizeof(pattern6_array)];
  uint8_t pattern7[sizeof(pattern7_array)];
  uint8_t pattern8[sizeof(pattern8_array)];
  uint8_t pattern9[sizeof(pattern9_array)];
  uint8_t pattern10[sizeof(pattern10_array)];
  uint8_t pattern11[sizeof(pattern11_array)];
  uint8_t pattern12[sizeof(pattern12_array)];
  uint8_t pattern13[sizeof(pattern13_array)];
  uint8_t pattern14[sizeof(pattern14_array)];
  uint8_t pattern15[sizeof(pattern15_array)];
  uint8_t pattern16[sizeof(pattern16_array)];
  uint8_t pattern17[sizeof(pattern17_array)];
  uint8_t pattern18[sizeof(pattern18_array)];
  uint8_t pattern19[sizeof(pattern19_array)];
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
      offsetof(struct score_data, pattern8),
      offsetof(struct score_data, pattern9),
      offsetof(struct score_data, pattern10),
      offsetof(struct score_data, pattern11),
      offsetof(struct score_data, pattern12),
      offsetof(struct score_data, pattern13),
      offsetof(struct score_data, pattern14),
      offsetof(struct score_data, pattern15),
      offsetof(struct score_data, pattern16),
      offsetof(struct score_data, pattern17),
      offsetof(struct score_data, pattern18),
      offsetof(struct score_data, pattern19),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry track (SQUARE)
    0x01,                         // Channel 1 entry track (SQUARE)
    0x02,                         // Channel 2 entry track (SQUARE)
    0x03,                         // Channel 3 entry track (NOISE)
  },
  .pattern0 = pattern0_data,
  .pattern1 = pattern1_data,
  .pattern2 = pattern2_data,
  .pattern3 = pattern3_data,
  .pattern4 = pattern4_data,
  .pattern5 = pattern5_data,
  .pattern6 = pattern6_data,
  .pattern7 = pattern7_data,
  .pattern8 = pattern8_data,
  .pattern9 = pattern9_data,
  .pattern10 = pattern10_data,
  .pattern11 = pattern11_data,
  .pattern12 = pattern12_data,
  .pattern13 = pattern13_data,
  .pattern14 = pattern14_data,
  .pattern15 = pattern15_data,
  .pattern16 = pattern16_data,
  .pattern17 = pattern17_data,
  .pattern18 = pattern18_data,
  .pattern19 = pattern19_data,
};

const PROGMEM struct sfx1_data {
  uint8_t fmt;
  uint8_t pattern0[13];
} pew = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(22),
    ATM_CMD_M_SET_VOLUME(63),
    ATM_CMD_I_NOTE_F5,
    ATM_CMD_M_DELAY_TICKS(3),
    ATM_CMD_I_NOTE_C4,
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_I_NOTE_C3,
    ATM_CMD_M_DELAY_TICKS(2),    
    ATM_CMD_I_NOTE_OFF,
    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_STOP,
  },
};

#endif

