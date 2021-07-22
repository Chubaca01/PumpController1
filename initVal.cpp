#include "EEPROM.h"
#include <UTFT.h>
#include <URTouch.h>
#include "Ticker.h"
#include "define.h"
#include "debug.h"
#include "initVal.h"
#include "pages.h"
#include "drawPage.h"

/*
#include "pumpTimer.h"
#include "message.h"
#include "command.h"*/

UTFT * myGLCD;
URTouch * myTouch;
Ticker * timer1Sec;

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
  pinMode(INT0, INPUT);


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
  attachInterrupt(digitalPinToInterrupt(INT0),readInputAndUpdate, CHANGE);
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

void initAllTimer(){
  // init loop timer 1 second
  //timer1Sec = new Ticker(updateTimer, 1000);
}

void initPages(){
  DebugPrintln("Init Pages");
  // home page
  headerPage1 = new pageObject("Pump Controller",10,32);
  quickCleanButton = new pageObject("Quick Clean",AXIS_1);
  speedButton = new pageObject("Run Speed",AXIS_2);
  setupButton = new pageObject("Setting Up",AXIS_3);
  boostButton = new pageObject("Boost Pump",AXIS_4);

  // speed page
  headerPage3 = new pageObject(" Speed  ",10,32);
  speedButton1 = new pageObject("Speed 1",AXIS_1);
  speedButton2 = new pageObject("Speed 2",AXIS_2);
  speedButton3 = new pageObject("Speed 3",AXIS_3);
  speedButton4 = new pageObject("Speed 4",AXIS_1);
  speedButton5 = new pageObject("Speed 5",AXIS_2);
  speedButton6 = new pageObject("Speed 6",AXIS_3);

  // bottom navigation bar
  buttonOnOff= new pageObject(POS_RIGHT);
  buttonHome1= new pageObject(POS_MIDDLE);
  buttonNext= new pageObject(POS_RIGHT);
  buttonPrev= new pageObject(POS_LEFT);
  buttonSave= new pageObject(POS_MIDDLE);
}
/*
void initAllTimer(){
char magicVal;

  // read Magic Value
  magicVal =  EEPROM.read(AD_MAGIC_VALUE);
  if (magicVal != MAGIC_VALUE){
    // nothing writing in EEPROM
    // write default values
    // write first only on time.
    DebugPrintln("Init Write Timer eeprom");
    eepWriteTimer(SPEED1_TIMER,AD_SPEED1_TIMER);
    eepWriteTimer(SPEED2_TIMER,AD_SPEED2_TIMER);
    eepWriteTimer(SPEED3_TIMER,AD_SPEED3_TIMER);
    eepWriteTimer(SPEED4_TIMER,AD_SPEED4_TIMER);
    eepWriteTimer(PRIME_TIMER,AD_PRIME_TIMER);
    eepWriteTimer(CLEAN_TIMER,AD_CLEAN_TIMER);
    eepWriteTimer(NIGHT_TIMER,AD_NIGHT_TIMER);
    eepWriteTimer(MORNING_TIMER,AD_MORNING_TIMER);
    // write magic valuue in EEPROM
    EEPROM.write(AD_MAGIC_VALUE,MAGIC_VALUE);
  }
  DebugPrintln("Init Read Timer eeprom");
  timer1Sec = new Ticker(updateTimer, 1000);
  runningTimer = new pumpTimer();
  initTimer(AD_MORNING_TIMER);
  initTimer(AD_NIGHT_TIMER);
  initTimer(AD_SPEED1_TIMER);
  initTimer(AD_SPEED2_TIMER);
  initTimer(AD_SPEED3_TIMER);
  initTimer(AD_SPEED4_TIMER);
  initTimer(AD_PRIME_TIMER);
  initTimer(AD_CLEAN_TIMER);
  initTimer(AD_NO_TIMER);
}

void initTimer(char addr)
{
  char TimerVal[4];
  eepReadTimer(TimerVal,4,addr);
  runningTimer->init(TimerVal[0],TimerVal[1],TimerVal[2],TimerVal[3]);
}

void initScreens(){



// home page
  headerPage1 = new page("Pump Controller",10,32);
  quickCleanButton = new page("Quick Clean",AXIS_1);
  speedButton = new page("Run Speed",AXIS_2);
  setupButton = new page("Setting Up",AXIS_3);
  boostButton = new page("Boost Pump",AXIS_4);

// setup page
  headerPage2 = new page("Setup",10,32);
  quickCleanTimerButton =new page("Quick Timer",AXIS_1);
  speedTimerButton = new page("Speeds Timer",AXIS_2);
  primeSpeedButton = new page("Prime Timer",AXIS_3);

// Quick clean header
  headerPage3 = new page("Quick Clean",10,32);


// Text and Button;
  text1 = new page(80,0);
  text2= new page(125,0);
  text0= new page(45,0);
  text3= new page(110,0);
//  buttonOnOff= new page(225,118,275,168);
  
  //buttonPress= new page(POS_CENTER);
  up1 = new page(40,70,80,110);
  up2 = new page(140,70,180,110);
  up3 = new page(240,70,280,110);
  down1 = new page(40,130,80,170);
  down2 = new page(140,130,180,170);
  down3 = new page(240,130,280,170);

// Select Speed Pages
headerPage5 = new page("Select Speed",10,32);

//Settings Header
headerPage6 = new page("Quick Timer Setting",10,32);
headerPage7 = new page("Speeds Timer Setting",10,32);
headerPage8 = new page("Prime Timer Setting",10,32);

// remote header
headerPage9 = new page(" Remote Ctrl",10,32);

// Boost pump header
headerPage10  = new page("Booter Pump",10,32);

speedButton1 = new page("Speed 1",AXIS_1);
speedButton2 = new page("Speed 2",AXIS_2);
speedButton3 = new page("Speed 3",AXIS_3);
speedButton4 = new page("Speed 4",AXIS_1);
speedButton5 = new page("Speed 5",AXIS_2);
speedButton6 = new page("Speed 6",AXIS_3);

// init message
cMessage = new message();
pumpMessage = new message();
sMessage = new message();
boostMessage = new message;
*/
