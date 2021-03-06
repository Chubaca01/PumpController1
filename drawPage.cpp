#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <define.h>
#include <pages.h>
#include <drawPage.h>
#include <debug.h>
#include <initVal.h>
#include <pumptimer.h>

  void drawContentRunning();

  // Page1 home page
  pageObject *headerPage1;
  pageObject *quickCleanButton;
  pageObject *speedButton;
  pageObject *setupButton;
  pageObject *boostButton;

  // Page2 quick clean
  pageObject *headerPage2;

  // Page3 speedButton;
  pageObject *headerPage3;
  pageObject *speedButton1;
  pageObject *speedButton2;
  pageObject *speedButton3;
  pageObject *speedButton4;
  pageObject *speedButton5;
  pageObject *speedButton6;

  // Page4 Setup Timer
  pageObject *headerPage4;
  pageObject *quickCleanTimerButton;
  pageObject *speedTimerButton;
  pageObject *boostDelayButton;
  pageObject *rpmSpeedButton;

  // Page5 Boost pump
  pageObject *headerPage5;

  // header setup page
  pageObject *headerPage6;
  pageObject *headerPage7;

  // remote page
  pageObject *headerPage8;

  // boost pump delay setting page
  pageObject *headerPage9;
  pageObject *boostDelayObj;

  // rpm speed setting page
  pageObject *headerPage10;

  // bottom navigation bar
  pageObject *buttonOnOff;
  pageObject *buttonHome1;
  pageObject *buttonNext;
  pageObject *buttonPrev;
  pageObject *buttonSave;

  // setting button
  pageObject *up1;
  pageObject *up2;
  pageObject *up3;
  pageObject *down1;
  pageObject *down2;
  pageObject *down3;

  // text object
  pageObject *text3;
  pageObject *text1;
  pageObject *text2;
  pageObject *text0;

  // rpm 0bject
  pageObject *rpm;

void drawHomePage(){
  // Title
  headerPage1->drawHeader();
  // Button - Quick Clean
  speedButton->drawButton();
  // Button - Run Speed
  quickCleanButton->drawButton();
  // Button - Setting Up
  setupButton->drawButton();
  // Button - boost pump
  boostButton->drawButton();
}

void drawQuickCleanPage(){
  // Title
  headerPage2->drawHeader();
  // draw Content
  drawContentRunning();
}


void drawSpeedPage1()
{
  // Title
  headerPage3->drawHeader();
  // button speed1
  speedButton1->drawButton();
  // button speed2
  speedButton2->drawButton();
  // button speed3
  speedButton3->drawButton();

  buttonHome1->setPos(POS_MIDDLE);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
  buttonNext->drawBitmp(next);
}

void drawSpeedPage2()
{
  // Title
  headerPage3->drawHeader();
  // button speed4
  speedButton4->drawButton();
  // button speed5
  speedButton5->drawButton();
  // button speed6
  speedButton6->drawButton();

  buttonHome1->setPos(POS_MIDDLE);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}

void drawSetupPage(){
  setupButton->eraseButton();
  headerPage4->drawHeader();
  quickCleanTimerButton->drawButton();
  speedTimerButton->drawButton();
  boostDelayButton->drawButton();
  buttonHome1->setPos(POS_MIDDLE);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
  buttonNext->drawBitmp(next);
}
void drawSetupPage2(){
  setupButton->eraseButton();
  headerPage4->drawHeader();
  rpmSpeedButton->drawButton();
  buttonHome1->setPos(POS_MIDDLE);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}
void drawRpmRemoteData(){
  int val;
  // display RPM data
  myGLCD->setColor(TEXT_COLOR); // Sets color to white
  val = rpm->curRemoteRpm;
  myGLCD->printNumI(rpm->rpmTab[val],139,80,4,'0');
}

void drawRemotePage(){
  // Title
  headerPage8->drawHeader();
  // text1
  text1->drawText("  Speed: ---- RPM",arial_normal,LEFT);
  buttonOnOff->setPos(POS_MIDDLE);
  buttonOnOff->drawBitmp(button_on);
  buttonHome1->setPos(POS_RIGHT);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
  drawRpmRemoteData();
}

void drawBoostDelayPage(){
  headerPage9->drawHeader();
  boostDelayObj->drawText(" Delay:",arial_normal,LEFT);
  up2->drawBitmp(up);
  down2->drawBitmp(down);
  drawBoostDelayDataSetting();
  buttonHome1->setPos(POS_RIGHT);
  buttonSave->drawBitmp(save);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}

void drawContentRunning(){
  // text1
  text1->drawText("  Speed: ---- RPM",arial_normal,LEFT);
  //text2
  text2->drawText("  Time:",arial_normal,LEFT);
  myGLCD->print(":",139,125);
  myGLCD->print(":",179,125);

  buttonOnOff->setPos(POS_MIDDLE);
  buttonOnOff->drawBitmp(button_off);
  buttonHome1->setPos(POS_RIGHT);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}

void drawRpm(int curTimer){
  int val;
  switch(curTimer){
    case(CLEAN):
    case(SPEED1):
    case(SPEED2):
    case(SPEED3):
    case(SPEED4):
    case(SPEED5):
    case(SPEED6):
      text0->setText("-- Running --");
    break;
    case(REMOTE):
      text0->setText("-- Running Remote --");
    break;
    case(NO_T):
      text0->setText("                ");
    break;
  }
  // display RPM data
  myGLCD->setColor(TEXT_COLOR); // Sets color to white
  val = rpm->rpmMod[curTimer];
  myGLCD->printNumI(rpm->rpmTab[val],139,80,4,'0');
}

void drawResetTimerData() {
  myGLCD->setColor(TEXT_COLOR);
  myGLCD->printNumI(0,110,125,2,'0');
  myGLCD->printNumI(0,150,125,2,'0');
  myGLCD->printNumI(0,190,125,2,'0');
  text0->eraseText(arial_normal,CENTER);
}

void drawBoostPage(){
  //title
  headerPage5->drawHeader();
  buttonOnOff->setPos(POS_CENTER);
  buttonOnOff->drawBitmp(button_off);
  buttonHome1->setPos(POS_MIDDLE);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}

void drawTimerSetup(int curTimer){
  switch (curTimer) {
    case CLEAN:
      headerPage6->drawHeader();
      break;
    case SPEED1:
    case SPEED2:
    case SPEED3:
    case SPEED4:
    case SPEED5:
    case SPEED6:
      headerPage7->drawHeader();
      break;
  }
  drawContentSetupTimer();
  runningTimer->initModVal(curTimer);
  drawTimerDataSetting(curTimer);
}

void drawRpmSetup(int curTimer){
  int val;
  switch (curTimer) {
    case CLEAN:
      headerPage6->drawHeader();
      break;
    case SPEED1:
    case SPEED2:
    case SPEED3:
    case SPEED4:
    case SPEED5:
    case SPEED6:
      headerPage7->drawHeader();
      break;
  }
  drawContentSetupRpm();
  rpm->initModVal(curTimer);
  val = rpm->rpmMod[curTimer];
  myGLCD->printNumI(rpm->rpmTab[val],128,110,4,'0');
}

void drawSpeedPage(int speed){
  // Title
  headerPage3->drawHeader();
  myGLCD->setColor(TEXT_COLOR);
  myGLCD->printNumI(speed,200,10,1,'0');
  // draw Content
  drawContentRunning();
}

void drawContentSetupTimer(){
  text0->drawText("   hr    mn    sec",arial_normal,LEFT);
  up1->drawBitmp(up);
  up2->drawBitmp(up);
  up3->drawBitmp(up);
  down1->drawBitmp(down);
  down2->drawBitmp(down);
  down3->drawBitmp(down);
  buttonSave->drawBitmp(save);
  buttonPrev->drawBitmp(prev);
  buttonNext->drawBitmp(next);
}

void drawContentSetupRpm(){
  rpm->drawText("   RPM:",arial_normal,LEFT);
  up2->drawBitmp(up);
  down2->drawBitmp(down);
  buttonHome1->setPos(POS_RIGHT);
  buttonSave->drawBitmp(save);
  buttonHome1->drawBitmp(button_home);
  buttonPrev->drawBitmp(prev);
}

void drawSetupRpmSpeed(char speedId){
  // Title
  headerPage10->drawHeader();
  drawContentSetupRpm();
  rpm->initRpmTabMod(speedId);
  myGLCD->printNumI(rpm->rpmTab[speedId],128,110,4,'0');
}

void drawTimerData(int curTimer){
  text0->blinkText(arial_normal,CENTER);
  myGLCD->printNumI(runningTimer->hourMod[curTimer],110,125,2,'0');
  myGLCD->printNumI(runningTimer->mnMod[curTimer],150,125,2,'0');
  myGLCD->printNumI(runningTimer->secMod[curTimer],190,125,2,'0');
}

void drawTimerDataSetting(int curTimer){
  myGLCD->printNumI(runningTimer->hourMod[curTimer],45,110,2,'0');
  myGLCD->printNumI(runningTimer->mnMod[curTimer],145,110,2,'0');
  myGLCD->printNumI(runningTimer->secMod[curTimer],245,110,2,'0');
}

void drawRpmDataSetting(int curTimer){
  int val;
  val = rpm->rpmMod[curTimer];
  myGLCD->printNumI(rpm->rpmTab[val],128,110,4,'0');
}
void drawRpmDataSettingVal(char speedId){
  myGLCD->printNumI(rpm->rpmTabMod[speedId],128,110,4,'0');
}
void drawBoostDelayDataSetting(){
  int val;
  val = (int) boostDelayObj->boostDelayMod;
  myGLCD->printNumI(val,145,110,2,'0');
}
void drawButton(int mode){
  if(mode == ON)
    buttonOnOff->drawBitmp(button_on);
  else
    buttonOnOff->drawBitmp(button_off);
}
void drawSaved(int curTimer){
  text3->drawText(" --Saved -- ",arial_normal,CENTER);
  delay(2000);
  text3->drawText("            ",arial_normal,CENTER);
  drawTimerDataSetting(curTimer);
}

void drawSavedRpm(int curTimer){
  text3->drawText(" --Saved -- ",arial_normal,CENTER);
  delay(2000);
  text3->drawText("            ",arial_normal,CENTER);
  rpm->drawText("   RPM:",arial_normal,LEFT);
  drawRpmDataSetting(curTimer);
}
void drawSavedRpmVal(char speedId){
  text3->drawText(" --Saved -- ",arial_normal,CENTER);
  delay(2000);
  text3->drawText("            ",arial_normal,CENTER);
  rpm->drawText("   RPM:",arial_normal,LEFT);
  drawRpmDataSettingVal(speedId);
}
void drawSavedBoostDelay(){
  text3->drawText(" --Saved -- ",arial_normal,CENTER);
  delay(2000);
  text3->drawText("            ",arial_normal,CENTER);
  boostDelayObj->drawText(" Delay:",arial_normal,LEFT);
  drawBoostDelayDataSetting();
}
