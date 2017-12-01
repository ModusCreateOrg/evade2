#ifndef EVADE4CH_H
#define EVADE4CH_H
  
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
  
/* pattern (channel) / bytes = 27*/
#define evade4ch_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(64), \
    ATM_CMD_M_SET_TEMPO(21), \
    ATM_CMD_M_CALL(6), \
    ATM_CMD_M_CALL_REPEAT(7, 2), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_M_CALL_REPEAT(7, 3), \
    ATM_CMD_M_CALL(9), \
    ATM_CMD_M_CALL_REPEAT(10, 3), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL_REPEAT(10, 3), \
    ATM_CMD_M_CALL(12), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade4ch_pattern0_array, evade4ch_pattern0_data);
    
/* pattern (channel) / bytes = 29*/
#define evade4ch_pattern1_data { \
    ATM_CMD_M_SET_VOLUME(64), \
    ATM_CMD_M_CALL_REPEAT(13, 3), \
    ATM_CMD_M_CALL(14), \
    ATM_CMD_M_CALL_REPEAT(15, 3), \
    ATM_CMD_M_CALL(16), \
    ATM_CMD_M_CALL(17), \
    ATM_CMD_M_CALL(18), \
    ATM_CMD_M_CALL(19), \
    ATM_CMD_M_CALL(20), \
    ATM_CMD_M_CALL(21), \
    ATM_CMD_M_CALL(18), \
    ATM_CMD_M_CALL(19), \
    ATM_CMD_M_CALL(22), \
    ATM_CMD_M_SET_LOOP_PATTERN(1), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade4ch_pattern1_array, evade4ch_pattern1_data);
    
/* pattern (channel) / bytes = 23*/
#define evade4ch_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(64), \
    ATM_CMD_M_CALL_REPEAT(23, 3), \
    ATM_CMD_M_CALL(24), \
    ATM_CMD_M_CALL_REPEAT(23, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_CALL_REPEAT(23, 3), \
    ATM_CMD_M_CALL(24), \
    ATM_CMD_M_CALL_REPEAT(23, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade4ch_pattern2_array, evade4ch_pattern2_data);
    
/* pattern (channel) / bytes = 13*/
#define evade4ch_pattern3_data { \
    ATM_CMD_M_SET_VOLUME(64), \
    ATM_CMD_M_CALL_REPEAT(26, 7), \
    ATM_CMD_M_CALL(27), \
    ATM_CMD_M_CALL_REPEAT(28, 7), \
    ATM_CMD_M_CALL(29), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade4ch_pattern3_array, evade4ch_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade4ch_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern4_array, evade4ch_pattern4_data);
    
/* pattern (drum) / bytes = 7*/
#define evade4ch_pattern5_data { \
    ATM_CMD_M_SET_VOLUME(16), \
    ATM_CMD_M_SLIDE_VOL_ON(-8), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_SLIDE_VOL_OFF, \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern5_array, evade4ch_pattern5_data);
    
/* pattern (tune) / "C00|P00" / bytes = 17*/
#define evade4ch_pattern6_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern6_array, evade4ch_pattern6_data);
    
/* pattern (tune) / "C00|P01" / bytes = 17*/
#define evade4ch_pattern7_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(5), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern7_array, evade4ch_pattern7_data);
    
/* pattern (tune) / "C00|P03" / bytes = 9*/
#define evade4ch_pattern8_data { \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern8_array, evade4ch_pattern8_data);
    
/* pattern (tune) / "C00|P07" / bytes = 9*/
#define evade4ch_pattern9_data { \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(11), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(9), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern9_array, evade4ch_pattern9_data);
    
/* pattern (tune) / "C00|P08" / bytes = 17*/
#define evade4ch_pattern10_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern10_array, evade4ch_pattern10_data);
    
/* pattern (tune) / "C00|P11" / bytes = 21*/
#define evade4ch_pattern11_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern11_array, evade4ch_pattern11_data);
    
/* pattern (tune) / "C00|P15" / bytes = 19*/
#define evade4ch_pattern12_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D5, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern12_array, evade4ch_pattern12_data);
    
/* pattern (tune) / "C01|P00" / bytes = 11*/
#define evade4ch_pattern13_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(20), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern13_array, evade4ch_pattern13_data);
    
/* pattern (tune) / "C01|P03" / bytes = 23*/
#define evade4ch_pattern14_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_F5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern14_array, evade4ch_pattern14_data);
    
/* pattern (tune) / "C01|P04" / bytes = 19*/
#define evade4ch_pattern15_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern15_array, evade4ch_pattern15_data);
    
/* pattern (tune) / "C01|P07" / bytes = 29*/
#define evade4ch_pattern16_data { \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_F5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern16_array, evade4ch_pattern16_data);
    
/* pattern (tune) / "C01|P08" / bytes = 25*/
#define evade4ch_pattern17_data { \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern17_array, evade4ch_pattern17_data);
    
/* pattern (tune) / "C01|P09" / bytes = 25*/
#define evade4ch_pattern18_data { \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern18_array, evade4ch_pattern18_data);
    
/* pattern (tune) / "C01|P10" / bytes = 25*/
#define evade4ch_pattern19_data { \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern19_array, evade4ch_pattern19_data);
    
/* pattern (tune) / "C01|P11" / bytes = 25*/
#define evade4ch_pattern20_data { \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern20_array, evade4ch_pattern20_data);
    
/* pattern (tune) / "C01|P12" / bytes = 25*/
#define evade4ch_pattern21_data { \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C5, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern21_array, evade4ch_pattern21_data);
    
/* pattern (tune) / "C01|P15" / bytes = 25*/
#define evade4ch_pattern22_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A5_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern22_array, evade4ch_pattern22_data);
    
/* pattern (tune) / "C02|P00" / bytes = 65*/
#define evade4ch_pattern23_data { \
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
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern23_array, evade4ch_pattern23_data);
    
/* pattern (tune) / "C02|P03" / bytes = 65*/
#define evade4ch_pattern24_data { \
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
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern24_array, evade4ch_pattern24_data);
    
/* pattern (tune) / "C02|P07" / bytes = 65*/
#define evade4ch_pattern25_data { \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D2, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade4ch_pattern25_array, evade4ch_pattern25_data);
    
/* pattern (tune) / "C03|P00" / bytes = 19*/
#define evade4ch_pattern26_data { \
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
DEFINE_PATTERN(evade4ch_pattern26_array, evade4ch_pattern26_data);
    
/* pattern (tune) / "C03|P07" / bytes = 34*/
#define evade4ch_pattern27_data { \
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
DEFINE_PATTERN(evade4ch_pattern27_array, evade4ch_pattern27_data);
    
/* pattern (tune) / "C03|P08" / bytes = 25*/
#define evade4ch_pattern28_data { \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
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
DEFINE_PATTERN(evade4ch_pattern28_array, evade4ch_pattern28_data);
    
/* pattern (tune) / "C03|P15" / bytes = 34*/
#define evade4ch_pattern29_data { \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
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
DEFINE_PATTERN(evade4ch_pattern29_array, evade4ch_pattern29_data);
    
const PROGMEM struct evade4ch_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[30];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade4ch_pattern0[sizeof(evade4ch_pattern0_array)];
  uint8_t evade4ch_pattern1[sizeof(evade4ch_pattern1_array)];
  uint8_t evade4ch_pattern2[sizeof(evade4ch_pattern2_array)];
  uint8_t evade4ch_pattern3[sizeof(evade4ch_pattern3_array)];
  uint8_t evade4ch_pattern4[sizeof(evade4ch_pattern4_array)];
  uint8_t evade4ch_pattern5[sizeof(evade4ch_pattern5_array)];
  uint8_t evade4ch_pattern6[sizeof(evade4ch_pattern6_array)];
  uint8_t evade4ch_pattern7[sizeof(evade4ch_pattern7_array)];
  uint8_t evade4ch_pattern8[sizeof(evade4ch_pattern8_array)];
  uint8_t evade4ch_pattern9[sizeof(evade4ch_pattern9_array)];
  uint8_t evade4ch_pattern10[sizeof(evade4ch_pattern10_array)];
  uint8_t evade4ch_pattern11[sizeof(evade4ch_pattern11_array)];
  uint8_t evade4ch_pattern12[sizeof(evade4ch_pattern12_array)];
  uint8_t evade4ch_pattern13[sizeof(evade4ch_pattern13_array)];
  uint8_t evade4ch_pattern14[sizeof(evade4ch_pattern14_array)];
  uint8_t evade4ch_pattern15[sizeof(evade4ch_pattern15_array)];
  uint8_t evade4ch_pattern16[sizeof(evade4ch_pattern16_array)];
  uint8_t evade4ch_pattern17[sizeof(evade4ch_pattern17_array)];
  uint8_t evade4ch_pattern18[sizeof(evade4ch_pattern18_array)];
  uint8_t evade4ch_pattern19[sizeof(evade4ch_pattern19_array)];
  uint8_t evade4ch_pattern20[sizeof(evade4ch_pattern20_array)];
  uint8_t evade4ch_pattern21[sizeof(evade4ch_pattern21_array)];
  uint8_t evade4ch_pattern22[sizeof(evade4ch_pattern22_array)];
  uint8_t evade4ch_pattern23[sizeof(evade4ch_pattern23_array)];
  uint8_t evade4ch_pattern24[sizeof(evade4ch_pattern24_array)];
  uint8_t evade4ch_pattern25[sizeof(evade4ch_pattern25_array)];
  uint8_t evade4ch_pattern26[sizeof(evade4ch_pattern26_array)];
  uint8_t evade4ch_pattern27[sizeof(evade4ch_pattern27_array)];
  uint8_t evade4ch_pattern28[sizeof(evade4ch_pattern28_array)];
  uint8_t evade4ch_pattern29[sizeof(evade4ch_pattern29_array)];
} evade4ch = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade4ch_score_data),
  .patterns_offset = {
      offsetof(struct evade4ch_score_data, evade4ch_pattern0),
      offsetof(struct evade4ch_score_data, evade4ch_pattern1),
      offsetof(struct evade4ch_score_data, evade4ch_pattern2),
      offsetof(struct evade4ch_score_data, evade4ch_pattern3),
      offsetof(struct evade4ch_score_data, evade4ch_pattern4),
      offsetof(struct evade4ch_score_data, evade4ch_pattern5),
      offsetof(struct evade4ch_score_data, evade4ch_pattern6),
      offsetof(struct evade4ch_score_data, evade4ch_pattern7),
      offsetof(struct evade4ch_score_data, evade4ch_pattern8),
      offsetof(struct evade4ch_score_data, evade4ch_pattern9),
      offsetof(struct evade4ch_score_data, evade4ch_pattern10),
      offsetof(struct evade4ch_score_data, evade4ch_pattern11),
      offsetof(struct evade4ch_score_data, evade4ch_pattern12),
      offsetof(struct evade4ch_score_data, evade4ch_pattern13),
      offsetof(struct evade4ch_score_data, evade4ch_pattern14),
      offsetof(struct evade4ch_score_data, evade4ch_pattern15),
      offsetof(struct evade4ch_score_data, evade4ch_pattern16),
      offsetof(struct evade4ch_score_data, evade4ch_pattern17),
      offsetof(struct evade4ch_score_data, evade4ch_pattern18),
      offsetof(struct evade4ch_score_data, evade4ch_pattern19),
      offsetof(struct evade4ch_score_data, evade4ch_pattern20),
      offsetof(struct evade4ch_score_data, evade4ch_pattern21),
      offsetof(struct evade4ch_score_data, evade4ch_pattern22),
      offsetof(struct evade4ch_score_data, evade4ch_pattern23),
      offsetof(struct evade4ch_score_data, evade4ch_pattern24),
      offsetof(struct evade4ch_score_data, evade4ch_pattern25),
      offsetof(struct evade4ch_score_data, evade4ch_pattern26),
      offsetof(struct evade4ch_score_data, evade4ch_pattern27),
      offsetof(struct evade4ch_score_data, evade4ch_pattern28),
      offsetof(struct evade4ch_score_data, evade4ch_pattern29),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry track (SQUARE)
    0x01,                         // Channel 1 entry track (SQUARE)
    0x02,                         // Channel 2 entry track (SQUARE)
    0x03,                         // Channel 3 entry track (NOISE)
  },
  .evade4ch_pattern0 = evade4ch_pattern0_data,
  .evade4ch_pattern1 = evade4ch_pattern1_data,
  .evade4ch_pattern2 = evade4ch_pattern2_data,
  .evade4ch_pattern3 = evade4ch_pattern3_data,
  .evade4ch_pattern4 = evade4ch_pattern4_data,
  .evade4ch_pattern5 = evade4ch_pattern5_data,
  .evade4ch_pattern6 = evade4ch_pattern6_data,
  .evade4ch_pattern7 = evade4ch_pattern7_data,
  .evade4ch_pattern8 = evade4ch_pattern8_data,
  .evade4ch_pattern9 = evade4ch_pattern9_data,
  .evade4ch_pattern10 = evade4ch_pattern10_data,
  .evade4ch_pattern11 = evade4ch_pattern11_data,
  .evade4ch_pattern12 = evade4ch_pattern12_data,
  .evade4ch_pattern13 = evade4ch_pattern13_data,
  .evade4ch_pattern14 = evade4ch_pattern14_data,
  .evade4ch_pattern15 = evade4ch_pattern15_data,
  .evade4ch_pattern16 = evade4ch_pattern16_data,
  .evade4ch_pattern17 = evade4ch_pattern17_data,
  .evade4ch_pattern18 = evade4ch_pattern18_data,
  .evade4ch_pattern19 = evade4ch_pattern19_data,
  .evade4ch_pattern20 = evade4ch_pattern20_data,
  .evade4ch_pattern21 = evade4ch_pattern21_data,
  .evade4ch_pattern22 = evade4ch_pattern22_data,
  .evade4ch_pattern23 = evade4ch_pattern23_data,
  .evade4ch_pattern24 = evade4ch_pattern24_data,
  .evade4ch_pattern25 = evade4ch_pattern25_data,
  .evade4ch_pattern26 = evade4ch_pattern26_data,
  .evade4ch_pattern27 = evade4ch_pattern27_data,
  .evade4ch_pattern28 = evade4ch_pattern28_data,
  .evade4ch_pattern29 = evade4ch_pattern29_data,
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