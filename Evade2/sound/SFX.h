#ifndef SFX_H
#define SFX_H


const PROGMEM struct sfx1_data {
  uint8_t fmt;
  uint8_t pattern0[13];
} SFX_player_shoot = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(22),
    ATM_CMD_M_SET_VOLUME(110),
    ATM_CMD_M_SLIDE_FREQ_ON(-50),
    ATM_CMD_I_NOTE_E5,

    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_STOP,
  },
};


const PROGMEM struct SFX_enemy_shoot_data {
  uint8_t fmt;
  uint8_t pattern0[13];
} SFX_enemy_shoot = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(22),
    ATM_CMD_M_SET_VOLUME(110),
    ATM_CMD_M_SLIDE_FREQ_ON(50),
    ATM_CMD_I_NOTE_E4,
    ATM_CMD_M_DELAY_TICKS(11),
    ATM_CMD_I_STOP,
  },
};




const PROGMEM struct SFX_player_hit_data {
  uint8_t fmt;
  uint8_t pattern0[11];
} SFX_player_hit = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(1),
    ATM_CMD_M_SET_VOLUME(128),
    ATM_CMD_I_NOTE_F3,
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_I_NOTE_F2,
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_I_STOP,
  },
};



const PROGMEM struct SFX_next_attract_screen_data {
  uint8_t fmt;
  uint8_t pattern0[11];
} SFX_next_attract_screen = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(1),
    ATM_CMD_M_SET_VOLUME(80),
    ATM_CMD_I_NOTE_C5,
    ATM_CMD_M_DELAY_TICKS(1),
    ATM_CMD_I_NOTE_E5,
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_I_STOP,
  },
};


const PROGMEM struct SFX_next_attract_char_data {
  uint8_t fmt;
  uint8_t pattern0[11];
} SFX_next_attract_char = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(1),
    ATM_CMD_M_SET_VOLUME(80),
    ATM_CMD_I_NOTE_D5,
    ATM_CMD_M_DELAY_TICKS(1),
    ATM_CMD_I_STOP,
  },
};

#endif