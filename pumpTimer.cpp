#include <UTFT.h>
#include <URTouch.h>
#include "Ticker.h"
#include <define.h>
#include "debug.h"
#include "initVal.h"
#include "pages.h"
#include "drawPage.h"
#include <pumptimer.h>
#include "inputOutput.h"
#include "message.h"
//#include "command.h"


pumpTimer *runningTimer;


int pumpTimer::dec(int timer){
  if (( hourMod[timer] == 0)&&(mnMod[timer]==0)&&( secMod[timer]==0)){
    // stop timer
    stat[timer] = 0;
    return 1;
  }
  if ((mnMod[timer] == 0)&&(secMod[timer]==0)){
    if ( hourMod[timer] > 0)
       hourMod[timer] -=1;
  }
 if ( secMod[timer] == 0){
    if (mnMod[timer] == 0)
      mnMod[timer] = 59;
    else if (mnMod[timer] > 0 )
      mnMod[timer] -=1;
  }
  if ( secMod[timer] == 0)
       secMod[timer] = 59;
  else
       secMod[timer] -=1;

  if (( hourMod[timer] == 0)&&(mnMod[timer]==0)&&( secMod[timer]==0)){
    // stop timer
    stat[timer] = 0;
    return 1;
  }
  else
    return 0;
}

void pumpTimer::saveTimer(char addr,int timer){
  hour[timer] = hourMod[timer];
  mn[timer] = mnMod[timer];
  sec[timer] = secMod[timer];
  eepWriteTimer(timer,hour[timer],mn[timer],sec[timer],addr);
}


void pumpTimer::hourUp(int timer){
  if (hourMod[timer] < 24)
      hourMod[timer]++;
}
void pumpTimer::hourDown(int timer){
  if (hourMod[timer] > 0)
      hourMod[timer]--;
}
void pumpTimer::minUp(int timer){
  if (mnMod[timer] < 59)
     mnMod[timer]++;
}
void pumpTimer::minDown(int timer){
  if (mnMod[timer] > 0)
     mnMod[timer]--;
}
void pumpTimer::secUp(int timer){
  if (secMod[timer] < 59)
    secMod[timer]++;
}
void pumpTimer::secDown(int timer){
  if (secMod[timer] > 0)
    secMod[timer]--;
}

void startTimer(char curTimer){
  runningTimer->initModVal(curTimer);
  runningTimer->setCurrentTimer(curTimer);
  runningTimer->start(curTimer);
}

void stopTimer(char curTimer){
  runningTimer->stop(curTimer);
  runningTimer->setCurrentTimer(NO_T);
  drawResetTimerData();
}

void updateTimer(){
  int curTimer = runningTimer->currentTimer;
  // every second
  //  current Timer
  if (curTimer){
    // check if timer is running
   if(runningTimer->stat[curTimer]){
      if (runningTimer->dec(curTimer)){
         sendMessageTimerStop(curTimer);
         drawTimerData(curTimer);
      }
      else
      drawTimerData(curTimer);
   }
  }
}
