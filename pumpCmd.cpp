#include <UTFT.h>
#include <URTouch.h>
#include "Ticker.h"
#include "define.h"
#include "initVal.h"
#include "pages.h"
#include "drawPage.h"
#include "debug.h"
#include "pumpTimer.h"
#include "message.h"
#include "pumpCmd.h"

void ExecPumpCmd(char val1,int val2,int val3){
    digitalWrite(S3,val3);
    sw_pos[3]= val3;
    digitalWrite(S2,val2);
    sw_pos[2]= val2;
    digitalWrite(S1,val1);
    sw_pos[1]= val1;
    delay(500);
    // clear all message from interupt routine
    sMessage->clearMessage();
}

// pump command
void pumpCmd(int tCmd){
    int val;
    if (tCmd == CMD_START_SPEED1){
      val = rpm->rpm[SPEED1];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED2){
      val = rpm->rpm[SPEED2];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED3){
      val = rpm->rpm[SPEED3];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED4){
      val = rpm->rpm[SPEED4];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED5){
      val = rpm->rpm[SPEED5];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED6){
      val = rpm->rpm[SPEED6];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_CLEAN){
      val = rpm->rpm[CLEAN];
      //val = rpm->rpmTab[val];
    }
    else if (tCmd== CMD_STOP_PUMP){
      DebugPrintln("pump stopped");
      stopPumpDelay();
      // stop boost pump
      digitalWrite(BP,HIGH);
      // stop pump;
      ExecPumpCmd(HIGH,HIGH,HIGH);
      return;
    }
    else{ // start pump based on RPM
      val = tCmd;
    }
    switch (val) {
      case RPM_SPEED1_ID:
        ExecPumpCmd(LOW,HIGH,HIGH);
      break;
      case RPM_SPEED2_ID:
        ExecPumpCmd(HIGH,LOW,HIGH);
      break;
      case RPM_SPEED3_ID:
        ExecPumpCmd(LOW,LOW,HIGH);
      break;
      case RPM_SPEED4_ID:
        ExecPumpCmd(HIGH,HIGH,LOW);
      break;
      case RPM_SPEED5_ID:
        ExecPumpCmd(LOW,HIGH,LOW);
      break;
      case RPM_SPEED6_ID:
        ExecPumpCmd(HIGH,LOW,LOW);
      break;
      case RPM_CLEAN_ID:
        ExecPumpCmd(LOW,LOW,LOW);
      break;
    }
}

int getRpm(){
  if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return NO_RPM_ID;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return RPM_SPEED1_ID;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED2_ID;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED3_ID;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED4_ID;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED5_ID;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== LOW)){
      return RPM_SPEED6_ID;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == LOW) && (sw_pos[3]== LOW)){
      return RPM_CLEAN_ID;
  }
  return NO_RPM_ID;
}
void startBoostBump(){
}
void boostCmd(char bCmd){
  int val;
  if (bCmd == BOOST_ON)
    {
      val  = getRpm();
      if (val == NO_RPM_ID){
        // run pump
        pumpCmd(CMD_START_CLEAN);
        initPumpDelay();
      }
      else
      {
        // start boost pump
        digitalWrite(BP,LOW);
      }
      return;
    }
  else if (bCmd == BOOST_OFF)
    {
      // stop boost pump
      digitalWrite(BP,HIGH);
      // stop pump
      pumpCmd(CMD_STOP_PUMP);
      return;
    }
}

int checkBoostState(){
int val;
  val = digitalRead(BP);
  if (val == HIGH)
    return OFF;
  else
    return ON;
}

void checkPumpDelay(){
    if (boostDelayObj->boostDelayFlag){
      if (boostDelayObj->boostDelayCount == 0){
        DebugPrint("Booster Start");
        // start boost pump
        digitalWrite(BP,LOW);
        boostDelayObj->boostDelayFlag = 0;
        boostDelayObj->boostDelayCount = 0;
      }
      else
        boostDelayObj->boostDelayCount--;
    }
}

void initPumpDelay(){
  boostDelayObj->boostDelayCount = boostDelayObj->boostDelay;
  boostDelayObj->boostDelayFlag = 1;
}

void stopPumpDelay(){
  boostDelayObj->boostDelayFlag = 0;
  boostDelayObj->boostDelayCount = 0;
}
