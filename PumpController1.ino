#include <UTFT.h>
#include <URTouch.h>
#include "Ticker.h"
#include "define.h"
#include "initVal.h"
#include "pages.h"
#include "drawPage.h"

void setup() {
  // put your setup code here, to run once:
  DebugInit();
  initInputOutput();
  initScreen();
  initAllTimer();
  initPages();
  drawHomePage();
  currentPage = HOME;
}

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
      if (speedButton->isButtonPushed(x,y)){
        erasePageHeader();
        boostButton->eraseButton();
        drawSpeedPage1();
        currentPage = PSPEED1;
        break;
      }
    break;
    case QUICK_CLEAN:
    break;
    case PSPEED1:
    case SSPEED1:
      if (buttonHome1->isButtonPushed(x,y)){
        erasePage();
        drawHomePage();
        currentPage = HOME;
        break;
      }
    break;
    case PSPEED2:
    case SSPEED2:
    break;
    case SETUP:
    break;
    case DREMOTE:
    break;
  }
  // put your main code here, to run repeatedly:
  delay(20);
}

// interrupt function
void readInputAndUpdate(){
 // sMessage->sendMessage(SWITCH_POS_CHANGED);
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
