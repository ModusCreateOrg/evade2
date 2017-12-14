#ifndef EVADE2_01_STAGE_1_ALT_SMALLER_H
#define EVADE2_01_STAGE_1_ALT_SMALLER_H
  
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif
  
#ifndef NUM_PATTERNS
#define NUM_PATTERNS(struct_) (ARRAY_SIZE( ((struct_ *)0)->patterns_offset))
#endif
  
#ifndef DEFINE_PATTERN
#define DEFINE_PATTERN(pattern_id, values) const uint8_t pattern_id[] = values;
#endif
  
/* pattern (channel) / bytes = 53*/
#define evade2_01_stage_1_alt_smaller_pattern0_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_SET_TEMPO(18), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(6), \
    ATM_CMD_M_CALL(7), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_M_CALL(5), \
    ATM_CMD_M_CALL(6), \
    ATM_CMD_M_CALL(7), \
    ATM_CMD_M_CALL(8), \
    ATM_CMD_M_CALL(9), \
    ATM_CMD_M_CALL(10), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(12), \
    ATM_CMD_M_CALL(13), \
    ATM_CMD_M_CALL(11), \
    ATM_CMD_M_CALL(12), \
    ATM_CMD_M_CALL(14), \
    ATM_CMD_M_CALL(15), \
    ATM_CMD_M_CALL(16), \
    ATM_CMD_M_CALL(17), \
    ATM_CMD_M_CALL(18), \
    ATM_CMD_M_CALL(19), \
    ATM_CMD_M_CALL(17), \
    ATM_CMD_M_CALL(20), \
    ATM_CMD_M_CALL(21), \
    ATM_CMD_M_SET_LOOP_PATTERN(0), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern0_array, evade2_01_stage_1_alt_smaller_pattern0_data);
    
/* pattern (channel) / bytes = 1*/
#define evade2_01_stage_1_alt_smaller_pattern1_data { \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern1_array, evade2_01_stage_1_alt_smaller_pattern1_data);
    
/* pattern (channel) / bytes = 33*/
#define evade2_01_stage_1_alt_smaller_pattern2_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL_REPEAT(22, 3), \
    ATM_CMD_M_CALL(23), \
    ATM_CMD_M_CALL_REPEAT(22, 3), \
    ATM_CMD_M_CALL(23), \
    ATM_CMD_M_CALL_REPEAT(24, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_CALL_REPEAT(24, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_CALL_REPEAT(24, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_CALL_REPEAT(24, 3), \
    ATM_CMD_M_CALL(25), \
    ATM_CMD_M_SET_LOOP_PATTERN(2), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern2_array, evade2_01_stage_1_alt_smaller_pattern2_data);
    
/* pattern (channel) / bytes = 41*/
#define evade2_01_stage_1_alt_smaller_pattern3_data { \
    ATM_CMD_M_SET_VOLUME(110), \
    ATM_CMD_M_CALL_REPEAT(26, 15), \
    ATM_CMD_M_CALL(27), \
    ATM_CMD_M_CALL_REPEAT(26, 15), \
    ATM_CMD_M_CALL(28), \
    ATM_CMD_M_CALL_REPEAT(26, 15), \
    ATM_CMD_M_CALL(27), \
    ATM_CMD_M_CALL_REPEAT(26, 15), \
    ATM_CMD_M_CALL(28), \
    ATM_CMD_M_CALL_REPEAT(29, 3), \
    ATM_CMD_M_CALL(30), \
    ATM_CMD_M_CALL_REPEAT(29, 3), \
    ATM_CMD_M_CALL_REPEAT(31, 4), \
    ATM_CMD_M_SET_LOOP_PATTERN(3), \
    ATM_CMD_I_STOP, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern3_array, evade2_01_stage_1_alt_smaller_pattern3_data);
    
/* pattern (drum) / bytes = 6*/
#define evade2_01_stage_1_alt_smaller_pattern4_data { \
    ATM_CMD_M_SET_VOLUME(31), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_SET_VOLUME(0), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern4_array, evade2_01_stage_1_alt_smaller_pattern4_data);
    
/* pattern (tune) / "C00|P00" / bytes = 11*/
#define evade2_01_stage_1_alt_smaller_pattern5_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern5_array, evade2_01_stage_1_alt_smaller_pattern5_data);
    
/* pattern (tune) / "C00|P01" / bytes = 11*/
#define evade2_01_stage_1_alt_smaller_pattern6_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern6_array, evade2_01_stage_1_alt_smaller_pattern6_data);
    
/* pattern (tune) / "C00|P02" / bytes = 11*/
#define evade2_01_stage_1_alt_smaller_pattern7_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(16), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern7_array, evade2_01_stage_1_alt_smaller_pattern7_data);
    
/* pattern (tune) / "C00|P03" / bytes = 15*/
#define evade2_01_stage_1_alt_smaller_pattern8_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern8_array, evade2_01_stage_1_alt_smaller_pattern8_data);
    
/* pattern (tune) / "C00|P08" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern9_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern9_array, evade2_01_stage_1_alt_smaller_pattern9_data);
    
/* pattern (tune) / "C00|P09" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern10_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern10_array, evade2_01_stage_1_alt_smaller_pattern10_data);
    
/* pattern (tune) / "C00|P10" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern11_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern11_array, evade2_01_stage_1_alt_smaller_pattern11_data);
    
/* pattern (tune) / "C00|P11" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern12_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern12_array, evade2_01_stage_1_alt_smaller_pattern12_data);
    
/* pattern (tune) / "C00|P12" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern13_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern13_array, evade2_01_stage_1_alt_smaller_pattern13_data);
    
/* pattern (tune) / "C00|P15" / bytes = 17*/
#define evade2_01_stage_1_alt_smaller_pattern14_data { \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(10), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(8), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern14_array, evade2_01_stage_1_alt_smaller_pattern14_data);
    
/* pattern (tune) / "C00|P16" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern15_data { \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern15_array, evade2_01_stage_1_alt_smaller_pattern15_data);
    
/* pattern (tune) / "C00|P17" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern16_data { \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern16_array, evade2_01_stage_1_alt_smaller_pattern16_data);
    
/* pattern (tune) / "C00|P18" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern17_data { \
    ATM_CMD_I_NOTE_C4, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern17_array, evade2_01_stage_1_alt_smaller_pattern17_data);
    
/* pattern (tune) / "C00|P19" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern18_data { \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern18_array, evade2_01_stage_1_alt_smaller_pattern18_data);
    
/* pattern (tune) / "C00|P20" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern19_data { \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern19_array, evade2_01_stage_1_alt_smaller_pattern19_data);
    
/* pattern (tune) / "C00|P22" / bytes = 9*/
#define evade2_01_stage_1_alt_smaller_pattern20_data { \
    ATM_CMD_I_NOTE_D4_, \
    ATM_CMD_M_DELAY_TICKS(22), \
    ATM_CMD_I_NOTE_G3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_G4_, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern20_array, evade2_01_stage_1_alt_smaller_pattern20_data);
    
/* pattern (tune) / "C00|P23" / bytes = 3*/
#define evade2_01_stage_1_alt_smaller_pattern21_data { \
    ATM_CMD_I_NOTE_F4, \
    ATM_CMD_M_DELAY_TICKS(32), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern21_array, evade2_01_stage_1_alt_smaller_pattern21_data);
    
/* pattern (tune) / "C02|P00" / bytes = 13*/
#define evade2_01_stage_1_alt_smaller_pattern22_data { \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(18), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern22_array, evade2_01_stage_1_alt_smaller_pattern22_data);
    
/* pattern (tune) / "C02|P03" / bytes = 19*/
#define evade2_01_stage_1_alt_smaller_pattern23_data { \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(12), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern23_array, evade2_01_stage_1_alt_smaller_pattern23_data);
    
/* pattern (tune) / "C02|P08" / bytes = 21*/
#define evade2_01_stage_1_alt_smaller_pattern24_data { \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(6), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern24_array, evade2_01_stage_1_alt_smaller_pattern24_data);
    
/* pattern (tune) / "C02|P11" / bytes = 25*/
#define evade2_01_stage_1_alt_smaller_pattern25_data { \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(4), \
    ATM_CMD_I_NOTE_A2_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_A3_, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_F3, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_NOTE_OFF, \
    ATM_CMD_M_DELAY_TICKS(2), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern25_array, evade2_01_stage_1_alt_smaller_pattern25_data);
    
/* pattern (tune) / "C03|P00" / bytes = 4*/
#define evade2_01_stage_1_alt_smaller_pattern26_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(7), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern26_array, evade2_01_stage_1_alt_smaller_pattern26_data);
    
/* pattern (tune) / "C03|P01" / bytes = 7*/
#define evade2_01_stage_1_alt_smaller_pattern27_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern27_array, evade2_01_stage_1_alt_smaller_pattern27_data);
    
/* pattern (tune) / "C03|P03" / bytes = 10*/
#define evade2_01_stage_1_alt_smaller_pattern28_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(1), \
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern28_array, evade2_01_stage_1_alt_smaller_pattern28_data);
    
/* pattern (tune) / "C03|P16" / bytes = 28*/
#define evade2_01_stage_1_alt_smaller_pattern29_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
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
    ATM_CMD_I_RETURN, \
}
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern29_array, evade2_01_stage_1_alt_smaller_pattern29_data);
    
/* pattern (tune) / "C03|P19" / bytes = 31*/
#define evade2_01_stage_1_alt_smaller_pattern30_data { \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
    ATM_CMD_M_CALL(4), \
    ATM_CMD_M_DELAY_TICKS(3), \
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
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern30_array, evade2_01_stage_1_alt_smaller_pattern30_data);
    
/* pattern (tune) / "C03|P23" / bytes = 13*/
#define evade2_01_stage_1_alt_smaller_pattern31_data { \
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
DEFINE_PATTERN(evade2_01_stage_1_alt_smaller_pattern31_array, evade2_01_stage_1_alt_smaller_pattern31_data);
    
const PROGMEM struct evade2_01_stage_1_alt_smaller_score_data {
  uint8_t fmt;
  uint8_t num_patterns;
  uint16_t patterns_offset[32];
  uint8_t num_channels;
  uint8_t start_patterns[4];
  uint8_t evade2_01_stage_1_alt_smaller_pattern0[sizeof(evade2_01_stage_1_alt_smaller_pattern0_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern1[sizeof(evade2_01_stage_1_alt_smaller_pattern1_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern2[sizeof(evade2_01_stage_1_alt_smaller_pattern2_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern3[sizeof(evade2_01_stage_1_alt_smaller_pattern3_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern4[sizeof(evade2_01_stage_1_alt_smaller_pattern4_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern5[sizeof(evade2_01_stage_1_alt_smaller_pattern5_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern6[sizeof(evade2_01_stage_1_alt_smaller_pattern6_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern7[sizeof(evade2_01_stage_1_alt_smaller_pattern7_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern8[sizeof(evade2_01_stage_1_alt_smaller_pattern8_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern9[sizeof(evade2_01_stage_1_alt_smaller_pattern9_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern10[sizeof(evade2_01_stage_1_alt_smaller_pattern10_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern11[sizeof(evade2_01_stage_1_alt_smaller_pattern11_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern12[sizeof(evade2_01_stage_1_alt_smaller_pattern12_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern13[sizeof(evade2_01_stage_1_alt_smaller_pattern13_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern14[sizeof(evade2_01_stage_1_alt_smaller_pattern14_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern15[sizeof(evade2_01_stage_1_alt_smaller_pattern15_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern16[sizeof(evade2_01_stage_1_alt_smaller_pattern16_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern17[sizeof(evade2_01_stage_1_alt_smaller_pattern17_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern18[sizeof(evade2_01_stage_1_alt_smaller_pattern18_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern19[sizeof(evade2_01_stage_1_alt_smaller_pattern19_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern20[sizeof(evade2_01_stage_1_alt_smaller_pattern20_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern21[sizeof(evade2_01_stage_1_alt_smaller_pattern21_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern22[sizeof(evade2_01_stage_1_alt_smaller_pattern22_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern23[sizeof(evade2_01_stage_1_alt_smaller_pattern23_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern24[sizeof(evade2_01_stage_1_alt_smaller_pattern24_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern25[sizeof(evade2_01_stage_1_alt_smaller_pattern25_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern26[sizeof(evade2_01_stage_1_alt_smaller_pattern26_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern27[sizeof(evade2_01_stage_1_alt_smaller_pattern27_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern28[sizeof(evade2_01_stage_1_alt_smaller_pattern28_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern29[sizeof(evade2_01_stage_1_alt_smaller_pattern29_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern30[sizeof(evade2_01_stage_1_alt_smaller_pattern30_array)];
  uint8_t evade2_01_stage_1_alt_smaller_pattern31[sizeof(evade2_01_stage_1_alt_smaller_pattern31_array)];
} evade2_01_stage_1_alt_smaller = {
  .fmt = ATM_SCORE_FMT_FULL,
  .num_patterns = NUM_PATTERNS(struct evade2_01_stage_1_alt_smaller_score_data),
  .patterns_offset = {
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern0),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern1),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern2),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern3),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern4),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern5),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern6),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern7),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern8),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern9),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern10),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern11),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern12),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern13),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern14),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern15),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern16),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern17),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern18),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern19),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern20),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern21),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern22),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern23),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern24),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern25),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern26),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern27),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern28),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern29),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern30),
      offsetof(struct evade2_01_stage_1_alt_smaller_score_data, evade2_01_stage_1_alt_smaller_pattern31),
  },
  .num_channels = 4,
  .start_patterns = {
    0x00,                         // Channel 0 entry pattern (SQUARE)
    0x01,                         // Channel 1 entry pattern (SQUARE)
    0x02,                         // Channel 2 entry pattern (SQUARE)
    0x03,                         // Channel 3 entry pattern (NOISE)
  },
  .evade2_01_stage_1_alt_smaller_pattern0 = evade2_01_stage_1_alt_smaller_pattern0_data,
  .evade2_01_stage_1_alt_smaller_pattern1 = evade2_01_stage_1_alt_smaller_pattern1_data,
  .evade2_01_stage_1_alt_smaller_pattern2 = evade2_01_stage_1_alt_smaller_pattern2_data,
  .evade2_01_stage_1_alt_smaller_pattern3 = evade2_01_stage_1_alt_smaller_pattern3_data,
  .evade2_01_stage_1_alt_smaller_pattern4 = evade2_01_stage_1_alt_smaller_pattern4_data,
  .evade2_01_stage_1_alt_smaller_pattern5 = evade2_01_stage_1_alt_smaller_pattern5_data,
  .evade2_01_stage_1_alt_smaller_pattern6 = evade2_01_stage_1_alt_smaller_pattern6_data,
  .evade2_01_stage_1_alt_smaller_pattern7 = evade2_01_stage_1_alt_smaller_pattern7_data,
  .evade2_01_stage_1_alt_smaller_pattern8 = evade2_01_stage_1_alt_smaller_pattern8_data,
  .evade2_01_stage_1_alt_smaller_pattern9 = evade2_01_stage_1_alt_smaller_pattern9_data,
  .evade2_01_stage_1_alt_smaller_pattern10 = evade2_01_stage_1_alt_smaller_pattern10_data,
  .evade2_01_stage_1_alt_smaller_pattern11 = evade2_01_stage_1_alt_smaller_pattern11_data,
  .evade2_01_stage_1_alt_smaller_pattern12 = evade2_01_stage_1_alt_smaller_pattern12_data,
  .evade2_01_stage_1_alt_smaller_pattern13 = evade2_01_stage_1_alt_smaller_pattern13_data,
  .evade2_01_stage_1_alt_smaller_pattern14 = evade2_01_stage_1_alt_smaller_pattern14_data,
  .evade2_01_stage_1_alt_smaller_pattern15 = evade2_01_stage_1_alt_smaller_pattern15_data,
  .evade2_01_stage_1_alt_smaller_pattern16 = evade2_01_stage_1_alt_smaller_pattern16_data,
  .evade2_01_stage_1_alt_smaller_pattern17 = evade2_01_stage_1_alt_smaller_pattern17_data,
  .evade2_01_stage_1_alt_smaller_pattern18 = evade2_01_stage_1_alt_smaller_pattern18_data,
  .evade2_01_stage_1_alt_smaller_pattern19 = evade2_01_stage_1_alt_smaller_pattern19_data,
  .evade2_01_stage_1_alt_smaller_pattern20 = evade2_01_stage_1_alt_smaller_pattern20_data,
  .evade2_01_stage_1_alt_smaller_pattern21 = evade2_01_stage_1_alt_smaller_pattern21_data,
  .evade2_01_stage_1_alt_smaller_pattern22 = evade2_01_stage_1_alt_smaller_pattern22_data,
  .evade2_01_stage_1_alt_smaller_pattern23 = evade2_01_stage_1_alt_smaller_pattern23_data,
  .evade2_01_stage_1_alt_smaller_pattern24 = evade2_01_stage_1_alt_smaller_pattern24_data,
  .evade2_01_stage_1_alt_smaller_pattern25 = evade2_01_stage_1_alt_smaller_pattern25_data,
  .evade2_01_stage_1_alt_smaller_pattern26 = evade2_01_stage_1_alt_smaller_pattern26_data,
  .evade2_01_stage_1_alt_smaller_pattern27 = evade2_01_stage_1_alt_smaller_pattern27_data,
  .evade2_01_stage_1_alt_smaller_pattern28 = evade2_01_stage_1_alt_smaller_pattern28_data,
  .evade2_01_stage_1_alt_smaller_pattern29 = evade2_01_stage_1_alt_smaller_pattern29_data,
  .evade2_01_stage_1_alt_smaller_pattern30 = evade2_01_stage_1_alt_smaller_pattern30_data,
  .evade2_01_stage_1_alt_smaller_pattern31 = evade2_01_stage_1_alt_smaller_pattern31_data,
};

#endif