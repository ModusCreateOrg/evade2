#ifndef SFX_H
#define SFX_H


const PROGMEM struct sfx1_data {
  uint8_t fmt;
  uint8_t pattern0[13];
} SFX_player_shoot = {
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




const PROGMEM struct SFX_player_hit_data {
  uint8_t fmt;
  uint8_t pattern0[8];
} SFX_player_hit = {
  .fmt = ATM_SCORE_FMT_MINIMAL_MONO,
  .pattern0 = {
    ATM_CMD_M_SET_TEMPO(1),
    ATM_CMD_M_SET_VOLUME(100),
    ATM_CMD_I_NOTE_F5,
    ATM_CMD_M_DELAY_TICKS(2),
    ATM_CMD_I_STOP,
  },
};

#endif