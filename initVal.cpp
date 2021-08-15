#include "EEPROM.h"
#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <define.h>
#include <debug.h>
#include <initVal.h>
#include <pages.h>
#include <drawPage.h>
#include <pumpTimer.h>
#include <InputOutput.h>
#include <message.h>
#include <pumpCmd.h>

/*

#include "command.h"*/

UTFT * myGLCD;
URTouch * myTouch;
Ticker * timer1Sec;
Ticker * timerDelay;
// To memorise switch positon
int sw_pos[4];

// main page variables
int currentPage;
int buttonState;
int force;

void initInputOutput(){
  DebugPrintln("Init Input Output");

  // Set pin mode
  pinMode (OUT,OUTPUT);
  pinMode(IN,INPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  pinMode(X3, INPUT);
  pinMode(BP,OUTPUT);
  pinMode(IT0, INPUT);


  // set pump off
  digitalWrite(OUT,LOW);
  digitalWrite(S1,HIGH);
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);

  // update switch position
  sw_pos[3]=HIGH; // S3
  sw_pos[2]=HIGH; // S2
  sw_pos[1]=HIGH; // S1

  // set booster pump off
  digitalWrite(BP,HIGH);

  // set interrupt
  attachInterrupt(digitalPinToInterrupt(IT0),readInputAndUpdate, CHANGE);
}

void initScreen(){
  DebugPrintln("Init Screen");

  myGLCD = new UTFT(SETTING_SCREEN);
  myGLCD->InitLCD();
  myGLCD->clrScr();
  delay(100);
  myTouch = new URTouch(SETTING_TOUCH);
  myTouch->InitTouch();
  myTouch->setPrecision(PREC_MEDIUM);
}

void initPages(){
  DebugPrintln("Init Pages");
  // home page
  headerPage1 = new pageObject("Pump Controller",10,32);
  quickCleanButton = new pageObject("Quick Clean",AXIS_1);
  speedButton = new pageObject("Run Speed",AXIS_2);
  setupButton = new pageObject("Setting Up",AXIS_3);
  boostButton = new pageObject("Boost Pump",AXIS_4);

  // Quick clean page
  headerPage2 = new pageObject("Quick Clean",10,32);

  // speed page
  headerPage3 = new pageObject(" Speed  ",10,32);
  speedButton1 = new pageObject("Speed 1",AXIS_1);
  speedButton2 = new pageObject("Speed 2",AXIS_2);
  speedButton3 = new pageObject("Speed 3",AXIS_3);
  speedButton4 = new pageObject("Speed 4",AXIS_1);
  speedButton5 = new pageObject("Speed 5",AXIS_2);
  speedButton6 = new pageObject("Speed 6",AXIS_3);

  // setup page
  headerPage4 = new pageObject("Setup",10,32);
  quickCleanTimerButton =new pageObject("Quick Timer",AXIS_1);
  speedTimerButton = new pageObject("Speeds Timer",AXIS_2);
  boostDelayButton = new pageObject("Boost Delay",AXIS_3);
  rpmSpeedButton = new pageObject("Rpm Speed",AXIS_1);
  // Boost pump header
  headerPage5  = new pageObject("Booter Pump",10,32);

  //Settings Header
  headerPage6 = new pageObject("Quick Timer Setting",10,32);
  headerPage7 = new pageObject("Speeds Timer Setting",10,32);

  // remote page
  headerPage8 = new pageObject("-- Remote --",10,32);

  // boost pump delay setting page
  headerPage9 = new pageObject("-- Boost Delay --",10,32);
  boostDelayObj = new pageObject(110,0);

  // bottom navigation bar
  buttonOnOff= new pageObject(POS_RIGHT);
  buttonHome1= new pageObject(POS_MIDDLE);
  buttonNext= new pageObject(POS_RIGHT);
  buttonPrev= new pageObject(POS_LEFT);
  buttonSave= new pageObject(POS_MIDDLE);

  // button setting
  up1 = new pageObject(40,70,80,110);
  up2 = new pageObject(140,70,180,110);
  up3 = new pageObject(240,70,280,110);
  down1 = new pageObject(40,130,80,170);
  down2 = new pageObject(140,130,180,170);
  down3 = new pageObject(240,130,280,170);


  // Text init;
  text0= new pageObject(45,0);
  text1= new pageObject(80,0);
  text2= new pageObject(125,0);
  text3= new pageObject(110,0);
}

void initRpm() {
rpm = new pageObject(110,0);
rpm->initRpm(NO_T,0);
rpm->initRpm(CLEAN,eepReadRpmTimer(AD_RPM_CLEAN_TIMER));
rpm->initRpm(SPEED1,eepReadRpmTimer(AD_RPM_SPEED1_TIMER));
rpm->initRpm(SPEED2,eepReadRpmTimer(AD_RPM_SPEED2_TIMER));
rpm->initRpm(SPEED3,eepReadRpmTimer(AD_RPM_SPEED3_TIMER));
rpm->initRpm(SPEED4,eepReadRpmTimer(AD_RPM_SPEED4_TIMER));
rpm->initRpm(SPEED5,eepReadRpmTimer(AD_RPM_SPEED5_TIMER));
rpm->initRpm(SPEED6,eepReadRpmTimer(AD_RPM_SPEED6_TIMER));
rpm->rpmTab[NO_RPM_ID] = NO_RPM;
rpm->rpmTab[RPM_SPEED1_ID] = eepReadRpm(AD_RPM_SPEED1);
rpm->rpmTab[RPM_SPEED2_ID] = eepReadRpm(AD_RPM_SPEED2);
rpm->rpmTab[RPM_SPEED3_ID] = eepReadRpm(AD_RPM_SPEED3);
rpm->rpmTab[RPM_SPEED4_ID] = eepReadRpm(AD_RPM_SPEED4);
rpm->rpmTab[RPM_SPEED5_ID] = eepReadRpm(AD_RPM_SPEED5);
rpm->rpmTab[RPM_SPEED6_ID] = eepReadRpm(AD_RPM_SPEED6);
rpm->rpmTab[RPM_CLEAN_ID] = eepReadRpm(AD_RPM_CLEAN);
sMessage->sendMessage(CHECK_INPUT_VALUES);
}

void initTimer(char addr)
{
  char TimerVal[4];
  eepReadTimer(TimerVal,4,addr);
  runningTimer->init(TimerVal[0],TimerVal[1],TimerVal[2],TimerVal[3]);
}

void initBoostDelay(char addr){
  int val;
  val = eeReadBoostDelay(addr);
  boostDelayObj->initBoostDelay(val);
}
void initAllTimer(){
  runningTimer = new pumpTimer();
  // init loop timer 1 second
  timer1Sec = new Ticker(updateTimer, 1000);
  timerDelay = new Ticker(checkPumpDelay, 1000);

  initTimer(AD_SPEED1_TIMER);
  initTimer(AD_SPEED2_TIMER);
  initTimer(AD_SPEED3_TIMER);
  initTimer(AD_SPEED4_TIMER);
  initTimer(AD_SPEED5_TIMER);
  initTimer(AD_SPEED6_TIMER);
  initTimer(AD_CLEAN_TIMER);
  initTimer(AD_MORNING_TIMER);
  initTimer(AD_NIGHT_TIMER);
  initTimer(AD_NO_TIMER);
  initBoostDelay(AD_BOOST_DELAY);
  timer1Sec->start(); //start the ticker.
  timerDelay->start();
}

void initMessages(){
  cMessage = new message();
  pumpMessage = new message();
  sMessage = new message();
  boostMessage = new message;
}
