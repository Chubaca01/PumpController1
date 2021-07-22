#ifndef INITVAL_H_INCLUDED
#define INITVAL_H_INCLUDED
  void initInputOutput();
  void initScreen();
  void initAllTimer();
  void initPages();
  //void initTimer(char addr);
  // interrup function in PumpController.ino
  void readInputAndUpdate();
  // external var
  extern UTFT    *myGLCD; //Parameters for Arduiono Mega with Extention Board.
  extern URTouch *myTouch;
  extern Ticker *timer1Sec;

  extern int sw_pos[4];
  extern int currentPage;
  extern int buttonState;
  extern int force;

  extern unsigned short button_home[];

  extern uint8_t SmallFont[];
  extern uint8_t BigFont[];
#endif
