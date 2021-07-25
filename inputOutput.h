#ifndef INPUTOUTPUT_H_INCLUDED
#define INPUTOUTPUT_H_INCLUDED
  void eepWriteTimer(char curTimer,char h,char m,char s, char addr);
  void eepReadTimer(char *tab,char sizeTab,char addr);
  void checkEepromWrite();

  //int readInput(int X,int n,int S);
  //void readInputAndUpdate();
#endif
