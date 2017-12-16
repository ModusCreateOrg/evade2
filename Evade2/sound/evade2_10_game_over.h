#ifndef EVADE2_10_GAME_OVER_H
#define EVADE2_10_GAME_OVER_H
  
/* pattern (channel) / bytes = 7*/
#define evade2_10_game_over_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_SET_TEMPO(8), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern0_array, evade2_10_game_over_pattern0_data);
    
/* pattern (channel) / bytes = 5*/
#define evade2_10_game_over_pattern1_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern1_array, evade2_10_game_over_pattern1_data);
    
/* pattern (channel) / bytes = 5*/
#define evade2_10_game_over_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL(6), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern2_array, evade2_10_game_over_pattern2_data);
    
/* pattern (channel) / bytes = 3*/
#define evade2_10_game_over_pattern3_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern3_array, evade2_10_game_over_pattern3_data);
    
/* pattern (tune) / "C00|P00" / bytes = 7*/
#define evade2_10_game_over_pattern4_data { \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_G4_, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern4_array, evade2_10_game_over_pattern4_data);
    
/* pattern (tune) / "C01|P00" / bytes = 7*/
#define evade2_10_game_over_pattern5_data { \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern5_array, evade2_10_game_over_pattern5_data);
    
/* pattern (tune) / "C02|P00" / bytes = 23*/
#define evade2_10_game_over_pattern6_data { \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_F2, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_10_game_over_pattern6_array, evade2_10_game_over_pattern6_data);
    
const PROGMEM struct evade2_10_game_over_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[7];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_10_game_over_pattern0[sizeof(evade2_10_game_over_pattern0_array)];
  uint8_t evade2_10_game_over_pattern1[sizeof(evade2_10_game_over_pattern1_array)];
  uint8_t evade2_10_game_over_pattern2[sizeof(evade2_10_game_over_pattern2_array)];
  uint8_t evade2_10_game_over_pattern3[sizeof(evade2_10_game_over_pattern3_array)];
  uint8_t evade2_10_game_over_pattern4[sizeof(evade2_10_game_over_pattern4_array)];
  uint8_t evade2_10_game_over_pattern5[sizeof(evade2_10_game_over_pattern5_array)];
  uint8_t evade2_10_game_over_pattern6[sizeof(evade2_10_game_over_pattern6_array)];
} evade2_10_game_over = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_10_game_over_score_data),
  .patterns_offset = {
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern0),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern1),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern2),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern3),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern4),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern5),
      offsetof(struct evade2_10_game_over_score_data, evade2_10_game_over_pattern6),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_10_game_over_pattern0 = evade2_10_game_over_pattern0_data,
  .evade2_10_game_over_pattern1 = evade2_10_game_over_pattern1_data,
  .evade2_10_game_over_pattern2 = evade2_10_game_over_pattern2_data,
  .evade2_10_game_over_pattern3 = evade2_10_game_over_pattern3_data,
  .evade2_10_game_over_pattern4 = evade2_10_game_over_pattern4_data,
  .evade2_10_game_over_pattern5 = evade2_10_game_over_pattern5_data,
  .evade2_10_game_over_pattern6 = evade2_10_game_over_pattern6_data,
};

#endif