#ifndef DRAWPAGES_H_INCLUDED
  #define DRAWPAGES_H_INCLUDED
  void drawHomePage();
  void drawSpeedPage1();
  void drawSpeedPage2();
  void drawSetupPage();
  void drawSetupPage2();
  void drawRemotePage();
  void drawQuickCleanPage();
  void drawResetTimerData();
  void drawRpm(int curTimer);
  void drawBoostPage();
  void drawTimerSetup(int curTimer);
  void drawRpmSetup(int curTimer);
  void drawSpeedPage(int speed);
  void drawContentSetupTimer();
  void drawContentSetupRpm();
  void drawTimerDataSetting(int curTimer);
  void drawRpmDataSetting(int curTimer);
  void drawTimerData(int curTimer);
  void drawButton(int mode);
  void drawSaved(int curTimer);
  void drawSavedRpm(int curTimer);
  void drawRpmRemoteData();
  void drawBoostDelayPage();
  void drawBoostDelayDataSetting();
  void drawSavedBoostDelay();
  void drawSetupRpmSpeed(char speedId);
  void drawRpmDataSettingVal(char speedId);
  void drawSavedRpmVal(char speedId);

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
  extern pageObject *boostDelayButton;
  extern pageObject *rpmSpeedButton;

  // Page5 Boost pump
  extern pageObject *headerPage5;

  // header setup page
  extern pageObject *headerPage6;
  extern pageObject *headerPage7;

  // remote page
  extern pageObject *headerPage8;

  // boost pump delay setting page
  extern pageObject *headerPage9;
  extern pageObject *boostDelayObj;

  // rpm speed setting page
  extern pageObject *headerPage10;

  // bottom navigation bar
  extern pageObject *buttonOnOff;
  extern pageObject *buttonHome1;
  extern pageObject *buttonNext;
  extern pageObject *buttonPrev;
  extern pageObject *buttonSave;

  // setting button
  extern pageObject *up1;
  extern pageObject *up2;
  extern pageObject *up3;
  extern pageObject *down1;
  extern pageObject *down2;
  extern pageObject *down3;


// text object
  extern pageObject *text3;
  extern pageObject *text1;
  extern pageObject *text2;
  extern pageObject *text0;

// rpm 0bject
  extern pageObject *rpm;

#endif
