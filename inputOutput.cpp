#include "EEPROM.h"
#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <define.h>
#include <debug.h>
#include <initVal.h>
#include <pages.h>
#include <drawPage.h>




// eeprom commands

void eepWriteTimer(char curTimer,char h,char m,char s, char addr){
  EEPROM.write(addr,curTimer);
  addr++;
  EEPROM.write(addr,h);
  addr++;
  EEPROM.write(addr,m);
  addr++;
  EEPROM.write(addr,s);
}
void eepReadTimer(char *tab,char sizeTab,char addr){
  int i;
  for (i= 0; i< sizeTab; i++){
    *tab = EEPROM.read(addr);
    tab++;
    addr++;
  }
}

void eepWriteRpmTimer(char rpmtab,char addr){
  EEPROM.write(addr,rpmtab);
}

int eepReadRpmTimer(char addr){
  int val;
  val = EEPROM.read(addr);
  return val;
}

void eepWriteRpm(int rpm,char addr){
  char val;

  // save high value
  val = (char) (rpm / 100);
  EEPROM.write(addr,val);
  addr++;
  // save low value
  val = (char) (rpm % 100);
  EEPROM.write(addr, val);
}

int eepReadRpm(char addr){
  int val,val1;
  // read high value
  val = EEPROM.read(addr) * 100;
  addr++;
  val1 = EEPROM.read(addr);
  // read lower value
  val = val + val1;

  DebugValPrintln(val);
  return val;
}

int eeReadBoostDelay(char addr){
  int val;
  val = EEPROM.read(addr);
  return val;
}
void eepWriteBoostDelay(char addr,char val){
  EEPROM.write(addr,val);
}

int readInput(int X,int n,int S){
int val;

  val = digitalRead(X);

  if (val != sw_pos[n]){
    //digitalWrite(S,val);
    sw_pos[n]=val;
    DebugPrint("Input Updated val:");
    DebugValPrintln(n);
    DebugValPrintln(val);
    return 1;
  }
  return 0;
}

void checkEepromWrite(){
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
    eepWriteTimer(SPEED5_TIMER,AD_SPEED5_TIMER);
    eepWriteTimer(SPEED6_TIMER,AD_SPEED6_TIMER);
    eepWriteTimer(CLEAN_TIMER,AD_CLEAN_TIMER);
    eepWriteTimer(NIGHT_TIMER,AD_NIGHT_TIMER);
    eepWriteTimer(MORNING_TIMER,AD_MORNING_TIMER);
    eepWriteTimer(NO_TIMER,AD_NO_TIMER);
    eepWriteRpmTimer(SPEED1,AD_RPM_SPEED1_TIMER);
    eepWriteRpmTimer(SPEED2,AD_RPM_SPEED2_TIMER);
    eepWriteRpmTimer(SPEED3,AD_RPM_SPEED3_TIMER);
    eepWriteRpmTimer(SPEED4,AD_RPM_SPEED4_TIMER);
    eepWriteRpmTimer(SPEED5,AD_RPM_SPEED5_TIMER);
    eepWriteRpmTimer(SPEED6,AD_RPM_SPEED6_TIMER);
    eepWriteRpmTimer(CLEAN,AD_RPM_CLEAN_TIMER);
    eepWriteRpm(RPM_SPEED1,AD_RPM_SPEED1);
    eepWriteRpm(RPM_SPEED2,AD_RPM_SPEED2);
    eepWriteRpm(RPM_SPEED3,AD_RPM_SPEED3);
    eepWriteRpm(RPM_SPEED4,AD_RPM_SPEED4);
    eepWriteRpm(RPM_SPEED5,AD_RPM_SPEED5);
    eepWriteRpm(RPM_SPEED6,AD_RPM_SPEED6);
    eepWriteRpm(RPM_CLEAN,AD_RPM_CLEAN);
    // save boost delay
    eepWriteBoostDelay(AD_BOOST_DELAY,BOOST_DELAY_VAL);

    // write magic valuue in EEPROM
    EEPROM.write(AD_MAGIC_VALUE,MAGIC_VALUE);
  }
}
