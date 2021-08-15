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

void checkRunningPage(int x,int y,char curTimer,char h,char m,char s,char rMessage,int bPrev,void (*fDraw)(void) );
void checkSettingTimerPage(int x,int y,char curTimer,int bPrev,int bNext,void (*fDraw)(void),char addr);
void checkSettingRpmPage(int x,int y,char curTimer,int bPrev,char addr);
void checkMessage();

void setup() {
  // put your setup code here, to run once:
  DebugInit();
  initInputOutput();
  initScreen();
  initPages();
  initMessages();
  drawHomePage();
  checkEepromWrite();
  initAllTimer();
  initRpm();
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
      drawRpm(NO_T);
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
      checkRunningPage(x,y,CLEAN_TIMER,CLEAN_TIMER_STOPPED,HOME,drawHomePage);
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
        drawRpm(NO_T);
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
        drawRpm(NO_T);
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
        drawRpm(NO_T);
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
          drawRpm(NO_T);
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
          drawRpm(NO_T);
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
          drawRpm(NO_T);
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
      if (boostDelayButton->isButtonPushed(x,y)){
        erasePage();
        drawBoostDelayPage();
        currentPage = BOOST_DELAY;
      }
      if (buttonHome1->isButtonPushed(x,y)){
        goHomePage();
        break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
         goHomePage();
         break;
      }
      if (buttonNext->isButtonPushed(x,y)){
         erasePage();
         drawSetupPage2();
         currentPage = SETUP_2;
         break;
      }
    break;
    case SETUP_2:
      if (buttonHome1->isButtonPushed(x,y)){
        goHomePage();
        break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
        erasePage();
        drawSetupPage();
        currentPage = SETUP;
        break;
      }
    break;
    case BOOST_PUMP:
    if (buttonOnOff->isButtonPushed(x,y,button_on)){
            if (!buttonState){
                buttonState = ON;
                // start boost pump
                boostMessage->sendMessage(BOOST_ON);
              }
              else{
                buttonState = OFF;
                // stop boost pump
                boostMessage->sendMessage(BOOST_OFF);
              }
              buttonOnOff->drawBitmp(button_off);
              return;
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
    case BOOST_DELAY:
      if (up2->isButtonPushed(x,y)){
        boostDelayObj->boostUp();
        drawBoostDelayDataSetting();
        break;
      }
      if (down2->isButtonPushed(x,y)){
        boostDelayObj->boostDown();
        drawBoostDelayDataSetting();
        break;
      }
      if (buttonSave->isButtonPushed(x,y)){
        boostDelayObj->saveBoostDelay(AD_BOOST_DELAY);
        drawSavedBoostDelay();
      }
      if (buttonHome1->isButtonPushed(x,y)){
       goHomePage();
       break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
        erasePage();
        drawSetupPage();
        currentPage = SETUP;
        break;
      }
    break;
    case DREMOTE:
    if (buttonOnOff->isButtonPushed(x,y)){
      if (!buttonState){
          drawButton(ON);
          buttonState = ON;
          drawRpmRemoteData();
          // start pump
          pumpCmd(rpm->curRemoteRpm);
          break;
        }
        else{
          drawButton(OFF);
          buttonState = OFF;
          drawRpm(NO_T);
          // stop pump
          sendPumpMessage(NO_T);
          break;
        }
     }
      if (buttonHome1->isButtonPushed(x,y)){
       // stop pump
       sendPumpMessage(NO_T);
       goHomePage();
       break;
      }
      if (buttonPrev->isButtonPushed(x,y)){
       // stop pump
       sendPumpMessage(NO_T);
       goHomePage();
       break;
      }
    break;
    case RSPEED1:
      checkRunningPage(x,y,SPEED1_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED2:
      checkRunningPage(x,y,SPEED2_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED3:
      checkRunningPage(x,y,SPEED3_TIMER,SPEED_TIMER_STOPPED,PSPEED1,drawSpeedPage1);
    break;
    case RSPEED4:
      checkRunningPage(x,y,SPEED4_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case RSPEED5:
      checkRunningPage(x,y,SPEED5_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case RSPEED6:
      checkRunningPage(x,y,SPEED6_TIMER,SPEED_TIMER_STOPPED,PSPEED2,drawSpeedPage2);
    break;
    case QTSETUP_CLEAN:
      checkSettingTimerPage(x,y,CLEAN,SETUP,QRSETUP_CLEAN,drawSetupPage,AD_CLEAN_TIMER);
    break;
    case QTSETUP_SPEED1:
      checkSettingTimerPage(x,y,SPEED1,SSPEED1,QRSETUP_SPEED1,drawSpeedPage1,AD_SPEED1_TIMER);
    break;
    case QTSETUP_SPEED2:
      checkSettingTimerPage(x,y,SPEED2,SSPEED1,QRSETUP_SPEED2,drawSpeedPage1,AD_SPEED2_TIMER);
    break;
    case QTSETUP_SPEED3:
      checkSettingTimerPage(x,y,SPEED3,SSPEED1,QRSETUP_SPEED3,drawSpeedPage1,AD_SPEED3_TIMER);
    break;
    case QTSETUP_SPEED4:
      checkSettingTimerPage(x,y,SPEED4,SSPEED2,QRSETUP_SPEED4,drawSpeedPage2,AD_SPEED4_TIMER);
    break;
    case QTSETUP_SPEED5:
      checkSettingTimerPage(x,y,SPEED5,SSPEED2,QRSETUP_SPEED4,drawSpeedPage2,AD_SPEED5_TIMER);
    break;
    case QTSETUP_SPEED6:
      checkSettingTimerPage(x,y,SPEED6,SSPEED2,QRSETUP_SPEED6,drawSpeedPage2,AD_SPEED6_TIMER);
    break;
    case QRSETUP_CLEAN:
      checkSettingRpmPage(x,y,CLEAN,QTSETUP_CLEAN,AD_RPM_CLEAN_TIMER);
    break;
    case QRSETUP_SPEED1:
      checkSettingRpmPage(x,y,SPEED1,QTSETUP_SPEED1,AD_RPM_SPEED1_TIMER);
    break;
    case QRSETUP_SPEED2:
      checkSettingRpmPage(x,y,SPEED2,QTSETUP_SPEED2,AD_RPM_SPEED2_TIMER);
    break;
    case QRSETUP_SPEED3:
      checkSettingRpmPage(x,y,SPEED3,QTSETUP_SPEED3,AD_RPM_SPEED3_TIMER);
    break;
    case QRSETUP_SPEED4:
      checkSettingRpmPage(x,y,SPEED4,QTSETUP_SPEED4,AD_RPM_SPEED4_TIMER);
    break;
    case QRSETUP_SPEED5:
      checkSettingRpmPage(x,y,SPEED5,QTSETUP_SPEED5,AD_RPM_SPEED5_TIMER);
    break;
    case QRSETUP_SPEED6:
      checkSettingRpmPage(x,y,SPEED6,QTSETUP_SPEED6,AD_RPM_SPEED6_TIMER);
    break;
  }
  checkMessage();
  timer1Sec->update();
  timerDelay->update();
}


// return to home page
void goHomePage(){
  erasePage();
  drawHomePage();
  currentPage = HOME;
}

// running page
void checkRunningPage(int x,int y,char curTimer,char h,char m,char s,char rMessage,int bPrev,void (*fDraw)(void) ){

      if (buttonOnOff->isButtonPushed(x,y)||(force==FORCE_ON)){
        if (!buttonState){
            drawButton(ON);
            force = FORCE_OFF;
            buttonState = ON;
            drawRpm(curTimer);
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
            drawRpm(NO_T);
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
void checkSettingTimerPage(int x,int y,char curTimer,int bPrev,int bNext,void (*fDraw)(void),char addr){

  //if (buttonHome1->isButtonPushed(x,y)){
  //  goHomePage();
  //  return;
  //}
  if (buttonPrev->isButtonPushed(x,y)){
    erasePage();
    (*fDraw)();
    currentPage = bPrev;
    return;
  }
  if (buttonNext->isButtonPushed(x,y)){
    erasePage();
    drawRpmSetup(curTimer);
    currentPage = bNext;
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

void checkSettingRpmPage(int x,int y,char curTimer,int bPrev,char addr){

  if (buttonHome1->isButtonPushed(x,y)){
    goHomePage();
    return;
  }
  if (buttonPrev->isButtonPushed(x,y)){
    erasePage();
    drawTimerSetup(curTimer);
    currentPage = bPrev;
    return;
  }
  if (up2->isButtonPushed(x,y)){
    rpm->rpmUp(curTimer);
    drawRpmDataSetting(curTimer);
    return;
  }
  if (down2->isButtonPushed(x,y)){
    rpm->rpmDown(curTimer);
    drawRpmDataSetting(curTimer);
    return;
  }

  if (buttonSave->isButtonPushed(x,y)){
    rpm->saveRpm(addr,curTimer);
    drawSavedRpm(curTimer);
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
  if(cMessage->isMessage()){
    mes = cMessage->getMessage();
    if((mes == SPEED_TIMER_STOPPED)||(mes == CLEAN_TIMER_STOPPED) ){
    // stop pump
    drawButton(OFF);
    buttonState = OFF;
    drawRpm(NO_T);
    stopTimer(runningTimer->currentTimer);
    sendPumpMessage(NO_T);
    }
  }
  if(sMessage->isMessage()){
    mes = sMessage->getMessage();
    if (mes == CHECK_INPUT_VALUES){
      delay(1000); //debounce
      readInput(X1,1,S1);
      readInput(X2,2,S2);
      readInput(X3,3,S3);
      val = getRpm();
      rpm->curRemoteRpm = val;
      if(val==NO_RPM_ID){
        if (currentPage != HOME){
          sendPumpMessage(NO_T);
          stopTimer(runningTimer->currentTimer);
          goHomePage();
        }
      }
      else{
        erasePage();
        drawRemotePage();
        buttonState = ON;
        pumpCmd(val);
        currentPage = DREMOTE ;
      }
    }
    sMessage->clearMessage();
  }
}


// interrupt function
void readInputAndUpdate(){
  sMessage->sendMessage(CHECK_INPUT_VALUES);
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
