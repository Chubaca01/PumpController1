#include <UTFT.h>
#include <URTouch.h>
#include "Ticker.h"
#include "pages.h"
#include "drawPage.h"
#include "define.h"
#include "debug.h"
#include "initVal.h"

// Page1
/*

// Page2
page *headerPage2;
page *quickCleanTimerButton;
page *speedTimerButton;
page *primeSpeedButton;

// Page 3
page *headerPage3;
page *text3;
page *text1;
page *text2;
page *text0;
page *buttonOnOff;
page *buttonHome1;
page *buttonNext;
page *buttonPrev;
page *up1;
page *up2;
page *up3;
page *down1;
page *down2;
page *down3;
page *buttonSave;

page *headerPage4;

page *headerPage5;
page *headerPage6;
page *headerPage7;
page *headerPage8;
page *headerPage9;
page *headerPage10;

page *speedButton1;
page *speedButton2;
page *speedButton3;
page *speedButton4;
page *speedButton5;
page *speedButton6;*/


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

int pageObject::isButtonPushed(int x,int y,unsigned short *pBitmap){
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

// function call
void erasePage(){
  myGLCD->clrScr();
}

void erasePageHeader(){
  // Title
  headerPage1->eraseHeader();
}
