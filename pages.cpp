#include <UTFT.h>
#include <URTouch.h>
#include <Ticker.h>
#include <string.h>
#include <define.h>
#include <pages.h>
#include <drawPage.h>
#include <define.h>
#include <debug.h>
#include <initVal.h>
#include "inputOutput.h"

int pageObject::isButtonPushed(int x,int y){
  if ((x>=posx1) && (x<=posx2) && (y>=posy1) && (y<=posy2)) {
    if(!isBitmap){
      myGLCD->setColor(LINE_COLOR_BUTTON_HIGH);
      myGLCD->drawRoundRect (posx1,posy1,posx2, posy2);
    }
    while (myTouch->dataAvailable())
      myTouch->read();
    return 1;
  }
  else
  return 0;
}

int pageObject::isButtonPushed(int x,int y,unsigned int *pBitmap){
  if ((x>=posx1) && (x<=posx2) && (y>=posy1) && (y<=posy2)) {
    drawBitmp(pBitmap);
    while (myTouch->dataAvailable())
      myTouch->read();
    return 1;
  }
  else
  return 0;
}

void pageObject::drawButton(){
  myGLCD->setColor(COLOR_BUTTON); // Sets green color
  myGLCD->fillRoundRect (posx1, posy1,posx2, posy2); // Draws filled rounded rectangle
  myGLCD->setColor(LINE_COLOR_BUTTON); // Sets color to white
  myGLCD->drawRoundRect (posx1, posy1, posx2, posy2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD->setFont(BigFont); // Sets the font to big
  myGLCD->setBackColor(BACK_TEXT_BUTTON); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD->print(text, CENTER, post); // Prints the string
}
void pageObject::eraseButton(){
  myGLCD->setColor(VGA_BLACK); // Sets green color
  myGLCD->fillRoundRect (posx1, posy1, posx2, posy2); // Draws filled rounded rectangle
  myGLCD->setColor(VGA_BLACK); // Sets color to white
  myGLCD->drawRoundRect (posx1, posy1, posx2, posy2); // Draws rounded rectangle without a fill, so the overall appearance of the button looks like it has a frame
  myGLCD->setFont(BigFont); // Sets the font to big
  myGLCD->setBackColor(VGA_BLACK); // Sets the background color of the area where the text will be printed to green, same as the button
  myGLCD->print("               ", CENTER, post); // Prints the string
}
void pageObject::drawHeader(){
  myGLCD->setBackColor(BACK_TEXT_COLOR); // Sets the background color of the area where the text will be printed to black
  myGLCD->setColor(TEXT_COLOR); // Sets color to white
  myGLCD->setFont(BigFont); // Sets font to big
  myGLCD->print(text, CENTER, post); // Prints the string on the screen
  myGLCD->setColor(LINE_COLOR); // Sets color to red
  myGLCD->drawLine(0,posy1,319,posy1); // Draws the line
}

void pageObject::eraseHeader(){
  myGLCD->setBackColor(BACK_TEXT_COLOR);
  myGLCD->setColor(ERASE_COLOR);
  myGLCD->print("                    ", CENTER, post);
}

void pageObject::drawText(char *t,uint8_t *tSize,int pos){
  myGLCD->setBackColor(BACK_TEXT_COLOR); // Sets the background color of the area where the text will be printed to black
  myGLCD->setColor(TEXT_COLOR); // Sets color to white
  myGLCD->setFont(tSize); // Sets font to big
  myGLCD->print(t,pos, post); // Prints the string on the screen
}

void pageObject::eraseText(uint8_t *tSize,int pos){
  myGLCD->setBackColor(BACK_TEXT_COLOR); // Sets the background color of the area where the text will be printed to black
  myGLCD->setColor(ERASE_COLOR); // Sets color to white
  myGLCD->setFont(tSize); // Sets font to big
  myGLCD->print("                    ",pos, post); // Prints the string on the screen
}

void pageObject::drawBitmp(unsigned int *pBitmap){
  int sizeX;
  int sizeY;
  sizeX = posx2-posx1;
  sizeY = posy2-posy1;
  myGLCD->drawBitmap (posx1,posy1, sizeX, sizeY, pBitmap);
}
void pageObject::blinkText(uint8_t *tSize,int pos){
  myGLCD->setBackColor(BACK_TEXT_COLOR); // Sets the background color of the area where the text will be printed to black
  myGLCD->setColor(TEXT_COLOR); // Sets color to white
  myGLCD->setFont(tSize); // Sets font to big
  if (!isblink){
    isblink = 1;

    myGLCD->print(text,pos,post);
  }
  else{
    isblink = 0;
    myGLCD->print("                        ",CENTER,post);
  }
}

void pageObject::rpmUp(int cur){
  if (rpmMod[cur] < MAX_RPM)
    rpmMod[cur] = rpmMod[cur]+1;
}

void pageObject::rpmDown(int cur){
  if (rpmMod[cur] > 1)
    rpmMod[cur] = rpmMod[cur]-1;
}

void pageObject::boostUp(){
  if (boostDelayMod < 60)
    boostDelayMod +=1;
}

void pageObject::boostDown(){
  if (boostDelayMod > 1)
    boostDelayMod -=1;
}

void pageObject::rpmTabUp(int cur){
  if (rpmTabMod[cur] < RPM_MAX)
    rpmTabMod[cur] = rpmTabMod[cur]+50;
}

void pageObject::rpmTabDown(int cur){
  if (rpmTabMod[cur] > RPM_MIN)
    rpmTabMod[cur] = rpmTabMod[cur]-50;
}

void pageObject::saveRpm(char addr,int timer){
  rpm[timer] = rpmMod[timer];
  DebugValPrintln(rpm[timer]);
  eepWriteRpmTimer(rpmMod[timer],addr);
}

void pageObject::saveRpmVal(char addr, char speedId){
  rpmTab[speedId] = rpmTabMod[speedId];
  eepWriteRpm(rpmTab[speedId],addr);
}

void pageObject::saveBoostDelay(char addr){
  boostDelay = boostDelayMod;
  eepWriteBoostDelay(addr,boostDelay);
}
// function call
void erasePage(){
  myGLCD->clrScr();
}

void erasePageHeader(){
  // Title
  headerPage1->eraseHeader();
}
