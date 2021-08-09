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

void eepWriteRpm(char rpmtab,char addr){
  EEPROM.write(addr,rpmtab);
}

int eepReadRpm(char addr){
  int val;
  val = EEPROM.read(addr);
  return val;
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
    eepWriteRpm(SPEED1,AD_RPM_SPEED1_TIMER);
    eepWriteRpm(SPEED2,AD_RPM_SPEED2_TIMER);
    eepWriteRpm(SPEED3,AD_RPM_SPEED3_TIMER);
    eepWriteRpm(SPEED4,AD_RPM_SPEED4_TIMER);
    eepWriteRpm(SPEED5,AD_RPM_SPEED5_TIMER);
    eepWriteRpm(SPEED6,AD_RPM_SPEED6_TIMER);
    eepWriteRpm(CLEAN,AD_RPM_CLEAN_TIMER);
    // write magic valuue in EEPROM
    EEPROM.write(AD_MAGIC_VALUE,MAGIC_VALUE);
  }
}
