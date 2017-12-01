#ifndef EVADE2_00_INTRO_H
#define EVADE2_00_INTRO_H
  
// #include "../src/ATMLib2/atm_cmd_constants.h"
  
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif
  
#ifndef NUM_PATTERNS
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))
#endif
  
#ifndef DEFINE_PATTERN
#define DEFINE_PATTERN(pattern_id, values) const uint8_t pattern_id[] = values;
#endif
  
/* pattern (channel) / bytes = 13*/
#define evade2_00_intro_pattern0_data { \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_SET_TEMPO(16), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(6), \
    ATM_CMD_M_CALL(7), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_00_intro_pattern0_array, evade2_00_intro_pattern0_data);
    
/* pattern (channel) / bytes = 11*/
#define evade2_00_intro_pattern1_data { \
    ATM_CMD_M_SET_LOOP_PATTERN(1), \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_CALL(9), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(12), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_00_intro_pattern1_array, evade2_00_intro_pattern1_data);
    
/* pattern (channel) / bytes = 6*/
#define evade2_00_intro_pattern2_data { \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_CALL_REPEAT(13, 4), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_00_intro_pattern2_array, evade2_00_intro_pattern2_data);
    
/* pattern (channel) / bytes = 11*/
#define evade2_00_intro_pattern3_data { \
    ATM_CMD_M_SET_VOLUME(32), \
    ATM_CMD_M_CALL(14), \
    ATM_CMD_M_CALL(15), \
    ATM_CMD_M_CALL(14), \
    ATM_CMD_M_CALL(16), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_00_intro_pattern3_array, evade2_00_intro_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade2_00_intro_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern4_array, evade2_00_intro_pattern4_data);
    
/* pattern (tune) / "C00|P00" / bytes = 5*/
#define evade2_00_intro_pattern5_data { \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(24), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern5_array, evade2_00_intro_pattern5_data);
    
/* pattern (tune) / "C00|P01" / bytes = 5*/
#define evade2_00_intro_pattern6_data { \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(24), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern6_array, evade2_00_intro_pattern6_data);
    
/* pattern (tune) / "C00|P02" / bytes = 3*/
#define evade2_00_intro_pattern7_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern7_array, evade2_00_intro_pattern7_data);
    
/* pattern (tune) / "C00|P03" / bytes = 13*/
#define evade2_00_intro_pattern8_data { \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern8_array, evade2_00_intro_pattern8_data);
    
/* pattern (tune) / "C01|P00" / bytes = 5*/
#define evade2_00_intro_pattern9_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(24), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern9_array, evade2_00_intro_pattern9_data);
    
/* pattern (tune) / "C01|P01" / bytes = 5*/
#define evade2_00_intro_pattern10_data { \
    ATM_CMD_I_NOTE_G3, \
    ATM_CMD_M_DELAY_TICKS(24), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern10_array, evade2_00_intro_pattern10_data);
    
/* pattern (tune) / "C01|P02" / bytes = 3*/
#define evade2_00_intro_pattern11_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern11_array, evade2_00_intro_pattern11_data);
    
/* pattern (tune) / "C01|P03" / bytes = 13*/
#define evade2_00_intro_pattern12_data { \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_G3, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G3, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern12_array, evade2_00_intro_pattern12_data);
    
/* pattern (tune) / "C02|P00" / bytes = 57*/
#define evade2_00_intro_pattern13_data { \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G2_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G2_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern13_array, evade2_00_intro_pattern13_data);
    
/* pattern (tune) / "C03|P00" / bytes = 13*/
#define evade2_00_intro_pattern14_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern14_array, evade2_00_intro_pattern14_data);
    
/* pattern (tune) / "C03|P01" / bytes = 16*/
#define evade2_00_intro_pattern15_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_00_intro_pattern15_array, evade2_00_intro_pattern15_data);
    
/* pattern (tune) / "C03|P03" / bytes = 25*/
#define evade2_00_intro_pattern16_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
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
DEFINE_PATTERN(evade2_00_intro_pattern16_array, evade2_00_intro_pattern16_data);
    
const PROGMEM struct evade2_00_intro_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[17];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_00_intro_pattern0[sizeof(evade2_00_intro_pattern0_array)];
  uint8_t evade2_00_intro_pattern1[sizeof(evade2_00_intro_pattern1_array)];
  uint8_t evade2_00_intro_pattern2[sizeof(evade2_00_intro_pattern2_array)];
  uint8_t evade2_00_intro_pattern3[sizeof(evade2_00_intro_pattern3_array)];
  uint8_t evade2_00_intro_pattern4[sizeof(evade2_00_intro_pattern4_array)];
  uint8_t evade2_00_intro_pattern5[sizeof(evade2_00_intro_pattern5_array)];
  uint8_t evade2_00_intro_pattern6[sizeof(evade2_00_intro_pattern6_array)];
  uint8_t evade2_00_intro_pattern7[sizeof(evade2_00_intro_pattern7_array)];
  uint8_t evade2_00_intro_pattern8[sizeof(evade2_00_intro_pattern8_array)];
  uint8_t evade2_00_intro_pattern9[sizeof(evade2_00_intro_pattern9_array)];
  uint8_t evade2_00_intro_pattern10[sizeof(evade2_00_intro_pattern10_array)];
  uint8_t evade2_00_intro_pattern11[sizeof(evade2_00_intro_pattern11_array)];
  uint8_t evade2_00_intro_pattern12[sizeof(evade2_00_intro_pattern12_array)];
  uint8_t evade2_00_intro_pattern13[sizeof(evade2_00_intro_pattern13_array)];
  uint8_t evade2_00_intro_pattern14[sizeof(evade2_00_intro_pattern14_array)];
  uint8_t evade2_00_intro_pattern15[sizeof(evade2_00_intro_pattern15_array)];
  uint8_t evade2_00_intro_pattern16[sizeof(evade2_00_intro_pattern16_array)];
} evade2_00_intro = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_00_intro_score_data),
  .patterns_offset = {
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern0),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern1),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern2),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern3),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern4),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern5),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern6),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern7),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern8),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern9),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern10),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern11),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern12),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern13),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern14),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern15),
      offsetof(struct evade2_00_intro_score_data, evade2_00_intro_pattern16),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_00_intro_pattern0 = evade2_00_intro_pattern0_data,
  .evade2_00_intro_pattern1 = evade2_00_intro_pattern1_data,
  .evade2_00_intro_pattern2 = evade2_00_intro_pattern2_data,
  .evade2_00_intro_pattern3 = evade2_00_intro_pattern3_data,
  .evade2_00_intro_pattern4 = evade2_00_intro_pattern4_data,
  .evade2_00_intro_pattern5 = evade2_00_intro_pattern5_data,
  .evade2_00_intro_pattern6 = evade2_00_intro_pattern6_data,
  .evade2_00_intro_pattern7 = evade2_00_intro_pattern7_data,
  .evade2_00_intro_pattern8 = evade2_00_intro_pattern8_data,
  .evade2_00_intro_pattern9 = evade2_00_intro_pattern9_data,
  .evade2_00_intro_pattern10 = evade2_00_intro_pattern10_data,
  .evade2_00_intro_pattern11 = evade2_00_intro_pattern11_data,
  .evade2_00_intro_pattern12 = evade2_00_intro_pattern12_data,
  .evade2_00_intro_pattern13 = evade2_00_intro_pattern13_data,
  .evade2_00_intro_pattern14 = evade2_00_intro_pattern14_data,
  .evade2_00_intro_pattern15 = evade2_00_intro_pattern15_data,
  .evade2_00_intro_pattern16 = evade2_00_intro_pattern16_data,
};

#endif