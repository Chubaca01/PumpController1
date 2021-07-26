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
void pumpCmd(char tCmd){

    if (tCmd == CMD_START_SPEED1){
      ExecPumpCmd(LOW,HIGH,HIGH);
    }
    else if (tCmd == CMD_START_SPEED2){
      ExecPumpCmd(HIGH,LOW,HIGH);
    }
    else if (tCmd == CMD_START_SPEED3){
      ExecPumpCmd(LOW,LOW,HIGH);
    }
    else if (tCmd == CMD_START_SPEED4){
      ExecPumpCmd(HIGH,HIGH,LOW);
    }
    else if (tCmd == CMD_START_SPEED5){
      ExecPumpCmd(LOW,HIGH,LOW);
    }
    else if (tCmd == CMD_START_SPEED6){
      ExecPumpCmd(HIGH,LOW,LOW);
    }
    else if (tCmd == CMD_START_CLEAN){
      ExecPumpCmd(HIGH,LOW,LOW);
    }
    else if (tCmd== CMD_STOP_PUMP){
      ExecPumpCmd(HIGH,HIGH,HIGH);
    }
}

int getRpm(){
  if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return NO_RPM;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED1;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == LOW) && (sw_pos[3]== HIGH)){
      return RPM_SPEED2;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED3;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== LOW)){
      return RPM_SPEED4;
  }else if ((sw_pos[1] == HIGH) && (sw_pos[2] == LOW) && (sw_pos[3]== LOW)){
      return RPM_CLEAN;
  }else if ((sw_pos[1] == LOW) && (sw_pos[2] == HIGH) && (sw_pos[3]== HIGH)){
      return NO_RPM;
  }
  return NO_RPM;
}

void boostCmd(char bCmd){
  if (bCmd == BOOST_ON)
    {
      // run pump
      pumpCmd(CMD_START_SPEED4);
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
