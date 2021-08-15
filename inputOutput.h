#ifndef INPUTOUTPUT_H_INCLUDED
#define INPUTOUTPUT_H_INCLUDED
  void eepWriteTimer(char curTimer,char h,char m,char s, char addr);
  void eepReadTimer(char *tab,char sizeTab,char addr);
  void eepWriteRpmTimer(char rpmtab,char addr);
  void checkEepromWrite();
  int readInput(int X,int n,int S);
  int eepReadRpmTimer(char addr);
  int eeReadBoostDelay(char addr);
  void eepWriteBoostDelay(char addr,char val);
  void eepWriteRpm(int rpm,char addr);
  int eepReadRpm(char addr);
  //void readInputAndUpdate();
#endif
