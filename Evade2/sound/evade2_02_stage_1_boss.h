    // ATM_CMD_M_ARPEGGIO_ON(0b00010001, 0b01000001), \

#ifndef EVADE2_02_STAGE_1_BOSS_H
#define EVADE2_02_STAGE_1_BOSS_H
  
  /* pattern (channel) / bytes = 16*/
#define evade2_02_stage_1_boss_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_ARPEGGIO_ON(0b00010001, 0b01000001), \
    ATM_CMD_M_SET_TEMPO(18), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_M_CALL(9), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern0_array, evade2_02_stage_1_boss_pattern0_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_02_stage_1_boss_pattern1_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern1_array, evade2_02_stage_1_boss_pattern1_data);
    
/* pattern (channel) / bytes = 8*/
#define evade2_02_stage_1_boss_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_NOTECUT_ON(0), \
    ATM_CMD_M_CALL_REPEAT(6, 16), \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern2_array, evade2_02_stage_1_boss_pattern2_data);
    
/* pattern (channel) / bytes = 6*/
#define evade2_02_stage_1_boss_pattern3_data { \
    ATM_CMD_M_CALL_REPEAT(7, 16), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern3_array, evade2_02_stage_1_boss_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade2_02_stage_1_boss_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern4_array, evade2_02_stage_1_boss_pattern4_data);
    
/* pattern (tune) / "C00|P04" / bytes = 7*/
#define evade2_02_stage_1_boss_pattern5_data { \
    ATM_CMD_I_NOTE_B3, \
    ATM_CMD_M_DELAY_TICKS(26), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_B3, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern5_array, evade2_02_stage_1_boss_pattern5_data);
    
/* pattern (tune) / "C02|P00" / bytes = 3*/
#define evade2_02_stage_1_boss_pattern6_data { \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern6_array, evade2_02_stage_1_boss_pattern6_data);
    
/* pattern (tune) / "C03|P00" / bytes = 7*/
#define evade2_02_stage_1_boss_pattern7_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern7_array, evade2_02_stage_1_boss_pattern7_data);
    
/* pattern (tune) / "Pattern 10" / bytes = 7*/
#define evade2_02_stage_1_boss_pattern8_data { \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(26), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern8_array, evade2_02_stage_1_boss_pattern8_data);
    
/* pattern (tune) / "Pattern 11" / bytes = 7*/
#define evade2_02_stage_1_boss_pattern9_data { \
    ATM_CMD_I_NOTE_A4, \
    ATM_CMD_M_DELAY_TICKS(26), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_A4, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern9_array, evade2_02_stage_1_boss_pattern9_data);
    
/* pattern (tune) / "Pattern 12" / bytes = 7*/
#define evade2_02_stage_1_boss_pattern10_data { \
    ATM_CMD_I_NOTE_D5, \
    ATM_CMD_M_DELAY_TICKS(26), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_02_stage_1_boss_pattern10_array, evade2_02_stage_1_boss_pattern10_data);
    
const PROGMEM struct evade2_02_stage_1_boss_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[11];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_02_stage_1_boss_pattern0[sizeof(evade2_02_stage_1_boss_pattern0_array)];
  uint8_t evade2_02_stage_1_boss_pattern1[sizeof(evade2_02_stage_1_boss_pattern1_array)];
  uint8_t evade2_02_stage_1_boss_pattern2[sizeof(evade2_02_stage_1_boss_pattern2_array)];
  uint8_t evade2_02_stage_1_boss_pattern3[sizeof(evade2_02_stage_1_boss_pattern3_array)];
  uint8_t evade2_02_stage_1_boss_pattern4[sizeof(evade2_02_stage_1_boss_pattern4_array)];
  uint8_t evade2_02_stage_1_boss_pattern5[sizeof(evade2_02_stage_1_boss_pattern5_array)];
  uint8_t evade2_02_stage_1_boss_pattern6[sizeof(evade2_02_stage_1_boss_pattern6_array)];
  uint8_t evade2_02_stage_1_boss_pattern7[sizeof(evade2_02_stage_1_boss_pattern7_array)];
  uint8_t evade2_02_stage_1_boss_pattern8[sizeof(evade2_02_stage_1_boss_pattern8_array)];
  uint8_t evade2_02_stage_1_boss_pattern9[sizeof(evade2_02_stage_1_boss_pattern9_array)];
  uint8_t evade2_02_stage_1_boss_pattern10[sizeof(evade2_02_stage_1_boss_pattern10_array)];
} evade2_02_stage_1_boss = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_02_stage_1_boss_score_data),
  .patterns_offset = {
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern0),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern1),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern2),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern3),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern4),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern5),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern6),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern7),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern8),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern9),
      offsetof(struct evade2_02_stage_1_boss_score_data, evade2_02_stage_1_boss_pattern10),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_02_stage_1_boss_pattern0 = evade2_02_stage_1_boss_pattern0_data,
  .evade2_02_stage_1_boss_pattern1 = evade2_02_stage_1_boss_pattern1_data,
  .evade2_02_stage_1_boss_pattern2 = evade2_02_stage_1_boss_pattern2_data,
  .evade2_02_stage_1_boss_pattern3 = evade2_02_stage_1_boss_pattern3_data,
  .evade2_02_stage_1_boss_pattern4 = evade2_02_stage_1_boss_pattern4_data,
  .evade2_02_stage_1_boss_pattern5 = evade2_02_stage_1_boss_pattern5_data,
  .evade2_02_stage_1_boss_pattern6 = evade2_02_stage_1_boss_pattern6_data,
  .evade2_02_stage_1_boss_pattern7 = evade2_02_stage_1_boss_pattern7_data,
  .evade2_02_stage_1_boss_pattern8 = evade2_02_stage_1_boss_pattern8_data,
  .evade2_02_stage_1_boss_pattern9 = evade2_02_stage_1_boss_pattern9_data,
  .evade2_02_stage_1_boss_pattern10 = evade2_02_stage_1_boss_pattern10_data,
};

#endif