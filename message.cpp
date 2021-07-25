#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <define.h>
#include <pages.h>
#include <drawPage.h>
#include <debug.h>
#include <pumptimer.h>
#include <message.h>


message *cMessage;
message *pumpMessage;
message *sMessage;
message *boostMessage;

int message::isMessage(){
  if (isMes)
    return (1);
  else
    return(0);
}

void sendMessageTimerStop(char curTimer){
  switch(curTimer){
    case(CLEAN):
      cMessage->sendMessage(CLEAN_TIMER_STOPPED);
      break;
    case(SPEED1):
    case(SPEED2):
    case(SPEED3):
    case(SPEED4):
    case(SPEED5):
    case(SPEED6):
      cMessage->sendMessage(SPEED_TIMER_STOPPED);
      break;
  }
 }

 void sendPumpMessage(char curTimer){
  switch(curTimer){
    case(CLEAN):
      pumpMessage->sendMessage(CMD_START_CLEAN);
      break;
    case(SPEED1):
      pumpMessage->sendMessage(CMD_START_SPEED1);
      break;
    case(SPEED2):
      pumpMessage->sendMessage(CMD_START_SPEED2);
      break;
    case(SPEED3):
      pumpMessage->sendMessage(CMD_START_SPEED3);
      break;
    case(SPEED4):
      pumpMessage->sendMessage(CMD_START_SPEED4);
      break;
   case(SPEED5):
      pumpMessage->sendMessage(CMD_START_SPEED5);
      break;
   case(SPEED6):
      pumpMessage->sendMessage(CMD_START_SPEED6);
      break;
  case(NO_T):
      pumpMessage->sendMessage(CMD_STOP_PUMP);
      break;
  }
}
