#ifndef COMMAND_H_INCLUDED
  #define COMMAND_H_INCLUDED
  void pumpCmd(int tCmd);
  int getRpm();
  void boostCmd(char bCmd);
  int checkBoostState();
  void initPumpDelay();
  void checkPumpDelay();
  void startBoostBump();
  void stopPumpDelay();
#endif
