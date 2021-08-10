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
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED2){
      val = rpm->rpm[SPEED2];
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED3){
      val = rpm->rpm[SPEED3];
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED4){
      val = rpm->rpm[SPEED4];
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED5){
      val = rpm->rpm[SPEED5];
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_SPEED6){
      val = rpm->rpm[SPEED6];
      val = rpm->rpmTab[val];
    }
    else if (tCmd == CMD_START_CLEAN){
      val = rpm->rpm[CLEAN];
      val = rpm->rpmTab[val];
    }
    else if (tCmd== CMD_STOP_PUMP){
      DebugPrintln("pump stopped");
      ExecPumpCmd(HIGH,HIGH,HIGH);
      return;
    }
    else{ // start pump based on RPM
      val = tCmd;
    }
    switch (val) {
      case RPM_SPEED1:
        ExecPumpCmd(LOW,HIGH,HIGH);
      break;
      case RPM_SPEED2:
        ExecPumpCmd(HIGH,LOW,HIGH);
      break;
      case RPM_SPEED3:
        ExecPumpCmd(LOW,LOW,HIGH);
      break;
      case RPM_SPEED4:
        ExecPumpCmd(HIGH,HIGH,LOW);
      break;
      case RPM_SPEED5:
        ExecPumpCmd(LOW,HIGH,LOW);
      break;
      case RPM_SPEED6:
        ExecPumpCmd(HIGH,LOW,LOW);
      break;
      case RPM_CLEAN:
        ExecPumpCmd(LOW,LOW,LOW);
      break;
    }
}

int getRpm(){
  if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return NO_RPM;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return RPM_SPEED1;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED2;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED3;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED4;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED5;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== LOW)){
      return RPM_SPEED6;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == LOW) && (sw_pos[3]== LOW)){
      return RPM_CLEAN;
  }
  return NO_RPM;
}

void boostCmd(char bCmd){
  int val;
  if (bCmd == BOOST_ON)
    {
      val  = getRpm();
      if (val == NO_RPM){
        // run pump
        pumpCmd(CMD_START_CLEAN);
        val = boostDelayObj->getboostDelay();
        delay(val);
      }
      // start boost pump
      digitalWrite(BP,LOW);
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
