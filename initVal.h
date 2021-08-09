#ifndef INITVAL_H_INCLUDED
#define INITVAL_H_INCLUDED
  void initInputOutput();
  void initScreen();
  void initAllTimer();
  void initRpm();
  void initPages();
  void initMessages();
  //void initTimer(char addr);
  // interrup function in PumpController.ino
  void readInputAndUpdate();
  // external var
  extern UTFT    *myGLCD; //Parameters for Arduiono Mega with Extention Board.
  extern URTouch *myTouch;
  extern Ticker *timer1Sec;

  extern int sw_pos[];
  extern int currentPage;
  extern int buttonState;
  extern int force;

  extern unsigned int button_home[];
  extern unsigned int button_on[];
  extern unsigned int button_off[];
  extern unsigned int next[];
  extern unsigned int prev[];
  extern unsigned short up[];
  extern unsigned short down[];
  extern unsigned short save[];

  extern uint8_t SmallFont[];
  extern uint8_t BigFont[];
  extern uint8_t arial_normal[];
#endif
