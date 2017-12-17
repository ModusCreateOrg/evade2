#ifndef EVADE2_04_STAGE_2_BOSS_H
#define EVADE2_04_STAGE_2_BOSS_H
  

/* pattern (channel) / bytes = 8*/
#define evade2_04_stage_2_boss_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_SET_TEMPO(18), \
    ATM_CMD_M_CALL_REPEAT(6, 2), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern0_array, evade2_04_stage_2_boss_pattern0_data);
    
/* pattern (channel) / bytes = 3*/
#define evade2_04_stage_2_boss_pattern1_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern1_array, evade2_04_stage_2_boss_pattern1_data);
    
/* pattern (channel) / bytes = 6*/
#define evade2_04_stage_2_boss_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL_REPEAT(7, 2), \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern2_array, evade2_04_stage_2_boss_pattern2_data);
    
/* pattern (channel) / bytes = 6*/
#define evade2_04_stage_2_boss_pattern3_data { \
    ATM_CMD_M_CALL_REPEAT(8, 2), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern3_array, evade2_04_stage_2_boss_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade2_04_stage_2_boss_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern4_array, evade2_04_stage_2_boss_pattern4_data);
    
/* pattern (drum) / bytes = 10*/
#define evade2_04_stage_2_boss_pattern5_data { \
    ATM_CMD_M_NOISE_RETRIG_ON(4), \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_SLIDE_VOL_ON(-8), \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOISE_RETRIG_OFF, \
    ATM_CMD_M_SLIDE_VOL_OFF, \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern5_array, evade2_04_stage_2_boss_pattern5_data);
    
/* pattern (tune) / "C00|P00" / bytes = 29*/
#define evade2_04_stage_2_boss_pattern6_data { \
    ATM_CMD_I_NOTE_D6_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_NOTE_G6_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_G6, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_G5, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(9), \
    ATM_CMD_I_NOTE_C6, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern6_array, evade2_04_stage_2_boss_pattern6_data);
    
/* pattern (tune) / "C02|P00" / bytes = 65*/
#define evade2_04_stage_2_boss_pattern7_data { \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_C2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern7_array, evade2_04_stage_2_boss_pattern7_data);
    
/* pattern (tune) / "C03|P00" / bytes = 26*/
#define evade2_04_stage_2_boss_pattern8_data { \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_04_stage_2_boss_pattern8_array, evade2_04_stage_2_boss_pattern8_data);
    
const PROGMEM struct evade2_04_stage_2_boss_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[9];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_04_stage_2_boss_pattern0[sizeof(evade2_04_stage_2_boss_pattern0_array)];
  uint8_t evade2_04_stage_2_boss_pattern1[sizeof(evade2_04_stage_2_boss_pattern1_array)];
  uint8_t evade2_04_stage_2_boss_pattern2[sizeof(evade2_04_stage_2_boss_pattern2_array)];
  uint8_t evade2_04_stage_2_boss_pattern3[sizeof(evade2_04_stage_2_boss_pattern3_array)];
  uint8_t evade2_04_stage_2_boss_pattern4[sizeof(evade2_04_stage_2_boss_pattern4_array)];
  uint8_t evade2_04_stage_2_boss_pattern5[sizeof(evade2_04_stage_2_boss_pattern5_array)];
  uint8_t evade2_04_stage_2_boss_pattern6[sizeof(evade2_04_stage_2_boss_pattern6_array)];
  uint8_t evade2_04_stage_2_boss_pattern7[sizeof(evade2_04_stage_2_boss_pattern7_array)];
  uint8_t evade2_04_stage_2_boss_pattern8[sizeof(evade2_04_stage_2_boss_pattern8_array)];
} evade2_04_stage_2_boss = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_04_stage_2_boss_score_data),
  .patterns_offset = {
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern0),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern1),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern2),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern3),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern4),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern5),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern6),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern7),
      offsetof(struct evade2_04_stage_2_boss_score_data, evade2_04_stage_2_boss_pattern8),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_04_stage_2_boss_pattern0 = evade2_04_stage_2_boss_pattern0_data,
  .evade2_04_stage_2_boss_pattern1 = evade2_04_stage_2_boss_pattern1_data,
  .evade2_04_stage_2_boss_pattern2 = evade2_04_stage_2_boss_pattern2_data,
  .evade2_04_stage_2_boss_pattern3 = evade2_04_stage_2_boss_pattern3_data,
  .evade2_04_stage_2_boss_pattern4 = evade2_04_stage_2_boss_pattern4_data,
  .evade2_04_stage_2_boss_pattern5 = evade2_04_stage_2_boss_pattern5_data,
  .evade2_04_stage_2_boss_pattern6 = evade2_04_stage_2_boss_pattern6_data,
  .evade2_04_stage_2_boss_pattern7 = evade2_04_stage_2_boss_pattern7_data,
  .evade2_04_stage_2_boss_pattern8 = evade2_04_stage_2_boss_pattern8_data,
};

#endif