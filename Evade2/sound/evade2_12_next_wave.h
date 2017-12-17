#ifndef EVADE2_12_NEXT_WAVE_H
#define EVADE2_12_NEXT_WAVE_H
  
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif
  
#ifndef NUM_PATTERNS
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))
#endif
  
#ifndef DEFINE_PATTERN
#define DEFINE_PATTERN(pattern_id, values) const uint8_t pattern_id[] = values;
#endif
  
/* pattern (channel) / bytes = 7*/
#define evade2_12_next_wave_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_SET_TEMPO(15), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern0_array, evade2_12_next_wave_pattern0_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_12_next_wave_pattern1_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern1_array, evade2_12_next_wave_pattern1_data);
    
/* pattern (channel) / bytes = 6*/
#define evade2_12_next_wave_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL_REPEAT(6, 2), \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern2_array, evade2_12_next_wave_pattern2_data);
    
/* pattern (channel) / bytes = 4*/
#define evade2_12_next_wave_pattern3_data { \
    ATM_CMD_M_CALL_REPEAT(7, 2), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern3_array, evade2_12_next_wave_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade2_12_next_wave_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern4_array, evade2_12_next_wave_pattern4_data);
    
/* pattern (tune) / "C00|P00" / bytes = 17*/
#define evade2_12_next_wave_pattern5_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G5_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern5_array, evade2_12_next_wave_pattern5_data);
    
/* pattern (tune) / "C02|P00" / bytes = 17*/
#define evade2_12_next_wave_pattern6_data { \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern6_array, evade2_12_next_wave_pattern6_data);
    
/* pattern (tune) / "C03|P00" / bytes = 4*/
#define evade2_12_next_wave_pattern7_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_12_next_wave_pattern7_array, evade2_12_next_wave_pattern7_data);
    
const PROGMEM struct evade2_12_next_wave_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[8];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_12_next_wave_pattern0[sizeof(evade2_12_next_wave_pattern0_array)];
  uint8_t evade2_12_next_wave_pattern1[sizeof(evade2_12_next_wave_pattern1_array)];
  uint8_t evade2_12_next_wave_pattern2[sizeof(evade2_12_next_wave_pattern2_array)];
  uint8_t evade2_12_next_wave_pattern3[sizeof(evade2_12_next_wave_pattern3_array)];
  uint8_t evade2_12_next_wave_pattern4[sizeof(evade2_12_next_wave_pattern4_array)];
  uint8_t evade2_12_next_wave_pattern5[sizeof(evade2_12_next_wave_pattern5_array)];
  uint8_t evade2_12_next_wave_pattern6[sizeof(evade2_12_next_wave_pattern6_array)];
  uint8_t evade2_12_next_wave_pattern7[sizeof(evade2_12_next_wave_pattern7_array)];
} evade2_12_next_wave = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_12_next_wave_score_data),
  .patterns_offset = {
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern0),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern1),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern2),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern3),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern4),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern5),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern6),
      offsetof(struct evade2_12_next_wave_score_data, evade2_12_next_wave_pattern7),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_12_next_wave_pattern0 = evade2_12_next_wave_pattern0_data,
  .evade2_12_next_wave_pattern1 = evade2_12_next_wave_pattern1_data,
  .evade2_12_next_wave_pattern2 = evade2_12_next_wave_pattern2_data,
  .evade2_12_next_wave_pattern3 = evade2_12_next_wave_pattern3_data,
  .evade2_12_next_wave_pattern4 = evade2_12_next_wave_pattern4_data,
  .evade2_12_next_wave_pattern5 = evade2_12_next_wave_pattern5_data,
  .evade2_12_next_wave_pattern6 = evade2_12_next_wave_pattern6_data,
  .evade2_12_next_wave_pattern7 = evade2_12_next_wave_pattern7_data,
};

#endif