#ifndef DRAWPAGES_H_INCLUDED
  #define DRAWPAGES_H_INCLUDED
  void drawHomePage();
  void drawSpeedPage1();
  void drawSpeedPage2();
  
  
  /*void drawSetupPage();
  void erasePageHeader();
  void erasePage();
  void drawQuickCleanPage();
  void drawButton(int mode);
  void drawTimerData(int curTimer);
  void resetTimerData();
  void drawRpm(int type,int curTimer);
  void drawSpeedPage(int speed);
  
  void drawTimerSetup(int curTimer);
  void drawTimerDataSetting(int curTimer);
  void drawSaved(int curTimer);
  void drawRemotePage();
  void drawBoostPage();*/


  // Page1 home page external
  extern pageObject *headerPage1;
  extern pageObject *speedButton;
  extern pageObject *quickCleanButton;
  extern pageObject *setupButton;
  extern pageObject *boostButton;
 
  // Page2 quick clean
  extern pageObject *headerPage2;
  
  // Page3 speedButton;
  extern pageObject *headerPage3;
  extern pageObject *speedButton1;
  extern pageObject *speedButton2;
  extern pageObject *speedButton3;
  extern pageObject *speedButton4;
  extern pageObject *speedButton5;
  extern pageObject *speedButton6;
  
  // Page4 Setup Timer
  extern pageObject *headerPage4;
  extern pageObject *quickCleanTimerButton;
  extern pageObject *speedTimerButton;
  
  // Page5 Boost pump
  extern pageObject *headerPage5;

  // bottom navigation bar
  extern pageObject *buttonOnOff;
  extern pageObject *buttonHome1;
  extern pageObject *buttonNext;
  extern pageObject *buttonPrev;
  extern pageObject *buttonSave;
#endif
