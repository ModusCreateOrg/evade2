#ifndef EVADE2_11_GET_READY_H
#define EVADE2_11_GET_READY_H
  
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif
  
#ifndef NUM_PATTERNS
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))
#endif
  
#ifndef DEFINE_PATTERN
#define DEFINE_PATTERN(pattern_id, values) const uint8_t pattern_id[] = values;
#endif
  
/* pattern (channel) / bytes = 9*/
#define evade2_11_get_ready_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(120), \
    ATM_CMD_M_SLIDE_FREQ_ON(70), \
    ATM_CMD_M_SET_TEMPO(20), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_11_get_ready_pattern0_array, evade2_11_get_ready_pattern0_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_11_get_ready_pattern1_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_11_get_ready_pattern1_array, evade2_11_get_ready_pattern1_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_11_get_ready_pattern2_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_11_get_ready_pattern2_array, evade2_11_get_ready_pattern2_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_11_get_ready_pattern3_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_11_get_ready_pattern3_array, evade2_11_get_ready_pattern3_data);
    
/* pattern (tune) / "Pattern 1" / bytes = 3*/
#define evade2_11_get_ready_pattern4_data { \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_11_get_ready_pattern4_array, evade2_11_get_ready_pattern4_data);
    
const PROGMEM struct evade2_11_get_ready_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[5];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_11_get_ready_pattern0[sizeof(evade2_11_get_ready_pattern0_array)];
  uint8_t evade2_11_get_ready_pattern1[sizeof(evade2_11_get_ready_pattern1_array)];
  uint8_t evade2_11_get_ready_pattern2[sizeof(evade2_11_get_ready_pattern2_array)];
  uint8_t evade2_11_get_ready_pattern3[sizeof(evade2_11_get_ready_pattern3_array)];
  uint8_t evade2_11_get_ready_pattern4[sizeof(evade2_11_get_ready_pattern4_array)];
} evade2_11_get_ready = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_11_get_ready_score_data),
  .patterns_offset = {
      offsetof(struct evade2_11_get_ready_score_data, evade2_11_get_ready_pattern0),
      offsetof(struct evade2_11_get_ready_score_data, evade2_11_get_ready_pattern1),
      offsetof(struct evade2_11_get_ready_score_data, evade2_11_get_ready_pattern2),
      offsetof(struct evade2_11_get_ready_score_data, evade2_11_get_ready_pattern3),
      offsetof(struct evade2_11_get_ready_score_data, evade2_11_get_ready_pattern4),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_11_get_ready_pattern0 = evade2_11_get_ready_pattern0_data,
  .evade2_11_get_ready_pattern1 = evade2_11_get_ready_pattern1_data,
  .evade2_11_get_ready_pattern2 = evade2_11_get_ready_pattern2_data,
  .evade2_11_get_ready_pattern3 = evade2_11_get_ready_pattern3_data,
  .evade2_11_get_ready_pattern4 = evade2_11_get_ready_pattern4_data,
};

#endif