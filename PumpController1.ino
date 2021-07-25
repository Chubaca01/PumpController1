#include <Arduino.h>
#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <define.h>
#include <initVal.h>
#include <pages.h>
#include <drawPage.h>
#include <inputOutput.h>
#include <pumpTimer.h>
#include "pumpCmd.h"
#include "message.h"

void checkRunningPage(int x,int y,int rpm,char curTimer,char h,char m,char s,char rMessage,int bPrev,void (*fDraw)(void) );
void checkSettingPage(int x,int y,char curTimer,int bPrev,void (*fDraw)(void),char addr);
void checkMessage();

void setup() {
  // put your setup code here, to run once:
  DebugInit();
  initInputOutput();
  initScreen();
  initPages();
  initMessages();
  drawHomePage();
  initAllTimer();
  currentPage = HOME;
}


// Main loop
void loop() {
  int val;
  int x,y;
  x=-1;
  y=-1;


  if (myTouch->dataAvailable()) {
    myTouch->read();
    x=myTouch->getX(); // X coordinate where the screen has been pressed
    y=myTouch->getY(); // Y coordinates where the screen has been pressed
  }

  switch (currentPage){
    case HOME:
    if (quickCleanButton->isButtonPushed(x,y)){
      erasePage();
      drawQuickCleanPage();
      drawRpm(NO_RPM,NO_T);
      drawResetTimerData();
      buttonState = OFF;
      currentPage = QUICK_CLEAN ;
      break;
    }
    if (speedButton->isButtonPushed(x,y)){
      erasePageHeader();
      boostButton->eraseButton();
      drawSpeedPage1();
      currentPage = PSPEED1;
      break;
    }
    if (setupButton->isButtonPushed(x,y)){
      erasePageHeader();
      boostButton->eraseButton();
      drawSetupPage();
      currentPage = SETUP;
      break;
    }
    if (boostButton->isButtonPushed(x,y)){
      erasePage();
      // checkpump state
      val =checkBoostState();
      drawBoostPage();
      if (val == ON)
        buttonState = ON;
      else
        buttonState = OFF;
      currentPage = BOOST_PUMP;
      break;
    }
    break;
    case QUICK_CLEAN:
      checkRunningPage(x,y,RPM_CLEAN,CLEAN_TIMER,CLEAN_TIMER_STOPPED,HOME,drawHomePage);
    break;
    case PSPEED1:
    case SSPEED1:
      if (speedButton1->isButtonPushed(x,y)){
         erasePage();
        if (currentPage == SSPEED1){
          drawTimerSetup(SPEED1);
          currentPage = QTSETUP_SPEED1;
          break;
        }
        drawSpeedPage(SPEED1);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        currentPage = RSPEED1;
        break;
      }
      if (speedButton2->isButtonPushed(x,y)){
         erasePage();
         if (currentPage == SSPEED1){
          drawTimerSetup(SPEED2);
          currentPage = QTSETUP_SPEED2;
          break;
        }
        drawSpeedPage(SPEED2);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        currentPage = RSPEED2;
        break;
      }
      if (speedButton3->isButtonPushed(x,y)){
        erasePage();
        if (currentPage == SSPEED1){
          drawTimerSetup(SPEED3);
          currentPage = QTSETUP_SPEED3;
          break;
        }
        drawSpeedPage(SPEED3);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        currentPage = RSPEED3;
        break;
      }
      if (buttonHome1->isButtonPushed(x,y)){
        goHomePage();
        break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
        erasePage();
        if (currentPage == SSPEED1){
          drawSetupPage();
          currentPage = SETUP;
          break;
        }
        drawHomePage();
        currentPage = HOME;
         break;
      }
      if (buttonNext->isButtonPushed(x,y)){
        erasePage();
        drawSpeedPage2();
        if(currentPage == SSPEED1){
          currentPage = SSPEED2;
          break;
        }
        currentPage = PSPEED2;
        break;
      }
    break;
    case PSPEED2:
    case SSPEED2:
      if (speedButton4->isButtonPushed(x,y)){
          erasePage();
          if (currentPage == SSPEED2){
            drawTimerSetup(SPEED4);
            currentPage = QTSETUP_SPEED4;
            break;
          }
          drawSpeedPage(SPEED4);
          drawRpm(NO_RPM,NO_T);
          drawResetTimerData();
          buttonState = OFF;
          currentPage = RSPEED4;
          break;
        }
      if (speedButton5->isButtonPushed(x,y)){
          erasePage();
          if (currentPage == SSPEED2){
            drawTimerSetup(SPEED5);
            currentPage = QTSETUP_SPEED5;
            break;
          }
          drawSpeedPage(SPEED5);
          drawRpm(NO_RPM,NO_T);
          drawResetTimerData();
          buttonState = OFF;
          currentPage = RSPEED5;
          break;
        }
      if (speedButton6->isButtonPushed(x,y)){
          erasePage();
          if (currentPage == SSPEED2){
            drawTimerSetup(SPEED6);
            currentPage = QTSETUP_SPEED6;
            break;
          }
          drawSpeedPage(SPEED6);
          drawRpm(NO_RPM,NO_T);
          drawResetTimerData();
          buttonState = OFF;
          currentPage = RSPEED6;
          break;
        }
      if (buttonHome1->isButtonPushed(x,y)){
          goHomePage();
          break;
        }
      if (buttonPrev->isButtonPushed(x,y)){
          erasePage();
          drawSpeedPage1();
          if(currentPage == SSPEED2){
            currentPage = SSPEED1;
            break;
          }
          currentPage = PSPEED1;
          break;
      }
    break;
    case SETUP:
      if (quickCleanTimerButton->isButtonPushed(x,y)){
        erasePage();
        drawTimerSetup(CLEAN);
        currentPage = QTSETUP_CLEAN;
        break;
      }
      if (speedTimerButton->isButtonPushed(x,y)){
        erasePageHeader();
        drawSpeedPage1();
        currentPage = SSPEED1;
        break;
      }
      if (buttonHome1->isButtonPushed(x,y)){
        goHomePage();
        break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
         goHomePage();
         break;
      }
    break;
    case BOOST_PUMP:
      if (buttonHome1->isButtonPushed(x,y)){
        goHomePage();
        break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
          goHomePage();
          break;
        }
    break;
    case DREMOTE:
    break;
    case RSPEED1:
      checkRunningPage(x,y,RPM_SPEED1,SPEED1_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED2:
      checkRunningPage(x,y,RPM_SPEED2,SPEED2_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED3:
      checkRunningPage(x,y,RPM_SPEED3,SPEED3_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED4:
      checkRunningPage(x,y,RPM_SPEED4,SPEED4_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case RSPEED5:
      checkRunningPage(x,y,RPM_SPEED5,SPEED5_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case RSPEED6:
      checkRunningPage(x,y,RPM_SPEED6,SPEED6_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case QTSETUP_CLEAN:
      checkSettingPage(x,y,CLEAN,SETUP,drawSetupPage,AD_CLEAN_TIMER);
    break;
    case QTSETUP_SPEED1:
      checkSettingPage(x,y,SPEED1,SSPEED1,drawSpeedPage1,AD_SPEED1_TIMER);
    break;
    case QTSETUP_SPEED2:
      checkSettingPage(x,y,SPEED2,SSPEED1,drawSpeedPage1,AD_SPEED2_TIMER);
    break;
    case QTSETUP_SPEED3:
      checkSettingPage(x,y,SPEED3,SSPEED1,drawSpeedPage1,AD_SPEED3_TIMER);
    break;
    case QTSETUP_SPEED4:
      checkSettingPage(x,y,SPEED4,SSPEED2,drawSpeedPage2,AD_SPEED4_TIMER);
    break;
    case QTSETUP_SPEED5:
      checkSettingPage(x,y,SPEED5,SSPEED2,drawSpeedPage2,AD_SPEED5_TIMER);
    break;
    case QTSETUP_SPEED6:
      checkSettingPage(x,y,SPEED6,SSPEED2,drawSpeedPage2,AD_SPEED6_TIMER);
    break;

  }
  checkMessage();
  timer1Sec->update();
}


// return to home page
void goHomePage(){
  erasePage();
  drawHomePage();
  currentPage = HOME;
}

// running page
void checkRunningPage(int x,int y,int rpm,char curTimer,char h,char m,char s,char rMessage,int bPrev,void (*fDraw)(void) ){
char *mes;

      if (buttonOnOff->isButtonPushed(x,y)||(force==FORCE_ON)){
        if (!buttonState){
            drawButton(ON);
            force = FORCE_OFF;
            buttonState = ON;
            drawRpm(rpm,curTimer);
            // start pump
            startTimer(curTimer);
            // start pump
            sendPumpMessage(curTimer);
            drawTimerData(curTimer);
            return;
          }
          else{
            drawButton(OFF);
            buttonState = OFF;
            drawRpm(NO_RPM,NO_T);
            // stop pump
            sendPumpMessage(NO_T);
            stopTimer(curTimer);
          }
          return;
       }
       if (buttonHome1->isButtonPushed(x,y)){
        // stop pump
        sendPumpMessage(NO_T);
        stopTimer(curTimer);
        goHomePage();
        return;
       }
       if (buttonPrev->isButtonPushed(x,y)){
        // stop pump
        sendPumpMessage(NO_T);
        stopTimer(curTimer);
        erasePage();
        (*fDraw)();
        currentPage = bPrev;
        return;
       }
    }
void checkSettingPage(int x,int y,char curTimer,int bPrev,void (*fDraw)(void),char addr){

  if (buttonHome1->isButtonPushed(x,y)){
    goHomePage();
    return;
  }
  if (buttonPrev->isButtonPushed(x,y)){
    erasePage();
    (*fDraw)();
    currentPage = bPrev;
    return;
  }
  if (up1->isButtonPushed(x,y)){
    runningTimer->hourUp(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (up2->isButtonPushed(x,y)){
    runningTimer->minUp(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (up3->isButtonPushed(x,y)){
    runningTimer->secUp(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (down1->isButtonPushed(x,y)){
    runningTimer->hourDown(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (down2->isButtonPushed(x,y)){
    runningTimer->minDown(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (down3->isButtonPushed(x,y)){
    runningTimer->secDown(curTimer);
    drawTimerDataSetting(curTimer);
    return;
  }
  if (buttonSave->isButtonPushed(x,y)){
    runningTimer->saveTimer(addr,curTimer);
    drawSaved(curTimer);
  }
}
void checkMessage(){
char mes;
int val;

  if(pumpMessage->isMessage()){
    mes = pumpMessage->getMessage();
    pumpCmd(mes);
    pumpMessage->clearMessage();
  }
  if(boostMessage->isMessage()){
    mes = boostMessage->getMessage();
    boostCmd(mes);
    boostMessage->clearMessage();
  }
  if(sMessage->isMessage()){
    mes = sMessage->getMessage();
    delay(1000); //debounce
    readInput(X1,1,S1);
    readInput(X2,2,S2);
    readInput(X3,3,S3);
    val = getRpm();
    switch (val){
      case NO_RPM:
        sendPumpMessage(NO_T);
        stopTimer(runningTimer->currentTimer);
        erasePage();
        drawHomePage();
        currentPage = HOME;
        break;
      case RPM_CLEAN:
        erasePage();
        drawQuickCleanPage();
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = QUICK_CLEAN ;
        break;
      case RPM_SPEED1:
        erasePage();
        drawSpeedPage(SPEED1);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED1 ;
        break;
      case RPM_SPEED2:
        erasePage();
        drawSpeedPage(SPEED2);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED2;
        break;
      case RPM_SPEED3:
        erasePage();
        drawSpeedPage(SPEED3);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED3;
        break;
      case RPM_SPEED4:
        erasePage();
        drawSpeedPage(SPEED4);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED4;
        break;
      case RPM_SPEED5:
        erasePage();
        drawSpeedPage(SPEED5);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED5;
        break;
      case RPM_SPEED6:
        erasePage();
        drawSpeedPage(SPEED6);
        drawRpm(NO_RPM,NO_T);
        drawResetTimerData();
        buttonState = OFF;
        force = FORCE_ON;
        currentPage = RSPEED6;
        break;
    }
  }
}


// interrupt function
void readInputAndUpdate(){
  sMessage->sendMessage(SWITCH_POS_CHANGED);
}


//--------------------------- debug function ----------------------------
void DebugInit(){
  #ifdef DEBUG
      Serial.begin(115200);
      delay(2000);
  #endif
  DebugPrintln("--- Start Serial Monitor SEND_RCVE ---");
}

void DebugPrint(char *sValue) {
   #ifdef DEBUG
    Serial.print(sValue);
   #endif
}

void DebugValPrint(int value) {
  #ifdef DEBUG
   Serial.print(value);
  #endif
}

void DebugValPrintln(int value) {
  #ifdef DEBUG
   Serial.println(value);
  #endif
}

void DebugPrintln(char *sValue) {
  #ifdef DEBUG
    Serial.println(sValue);
  #endif
}
