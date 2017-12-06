#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "Process.h"
#include "Types.h"

// number of records in high score table
#define HIGH_SCORE_RECORDS 5
struct HighScoreRecord {
  char initials[3];
  BCD score;
  void dump();
};

class HighScore {
public:
  // returns TRUE if EEPROM has valid high score data
  static BOOL valid();
  // resets EEPROM high scores (will be valid)
  static void reset();
  // retursn index if score is a new high score
  // or -1
  static BYTE isHighScore(BCD score);
  // read a record, indexed, from EEPROM
  static BOOL readRecord(BYTE index, HighScoreRecord *r);
  // write a record, indexed, to EEPROM
  static BOOL writeRecord(BYTE index, HighScoreRecord *r);

public:
  static void renderHighScores();

public:
  // enter initials process
  static void initials_process(Process *me);

private:
  static void initials_loop(Process *me);
};

#endif
