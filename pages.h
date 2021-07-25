#ifndef PAGES_H_INCLUDED
  #define PAGES_H_INCLUDED
  class pageObject {
      char tText[50];
      char *text;
      int posx1,posx2,posy1,posy2,post;
      int isBitmap;
      int isblink;
    public:
    // constructor button
    pageObject(char *t,int px1,int py1,int px2,int py2,int px3){strcpy(tText,t);text=&tText[0];posx1=px1;posy1=py1;posx2=px2;posy2=py2;post=px3;isBitmap=0;isblink=0;}
    // constructor header
    pageObject(char *t,int px1,int py1){strcpy(tText,t);text=&tText[0];post=px1;posy1=py1;isBitmap=0;isblink=0;}
    // constructor text
    pageObject(int px1,int py1){text=&tText[0];post=px1;posy1=py1;isBitmap=0;isblink=0;}
    // constructor navigation bar
    pageObject(int px1,int py1,int px2,int py2){text=&tText[0];posx1=px1;posy1=py1;posx2=px2;posy2=py2;isBitmap=1;isblink=0;};
    void drawButton(void);
    void drawHeader(void);
    void eraseHeader(void);
    void eraseButton(void);
    void drawText(char *t, uint8_t *tSize,int pos);
    void eraseText(uint8_t *tSize,int pos);
    void drawBitmp(unsigned int *pBitmap);
    int isButtonPushed(int x,int y);
    int isButtonPushed(int x,int y,unsigned int *pBitmap);
    void setPos(int px1,int py1,int px2,int py2){posx1=px1;posy1=py1;posx2=px2;posy2=py2;};
    void blinkText(uint8_t *tSize,int pos);
    void setText(char *t){strcpy(tText,t);};
  };

  /*extern page *speedButton;
  extern page *quickCleanButton;
  extern page *setupButton;
  extern page *boostButton;
  extern page *headerPage1;

  extern page *headerPage2;
  extern page *quickCleanTimerButton;
  extern page *speedTimerButton;
  extern page *primeSpeedButton;

  extern page *headerPage3;
  extern page *text3;
  extern page *text1;
  extern page *text2;
  extern page *text0;
  extern page *buttonOnOff;
  extern page *buttonHome1;
  extern page *buttonNext;
  extern page *buttonPrev;
  extern page *up1;
  extern page *up2;
  extern page *up3;
  extern page *down1;
  extern page *down2;
  extern page *down3;
  extern page *buttonSave;

  extern page *headerPage4;

  extern page *headerPage5;
  extern page *headerPage6;
  extern page *headerPage7;
  extern page *headerPage8;
  extern page *headerPage9;
  extern page *headerPage10;

  extern page *speedButton1;
  extern page *speedButton2;
  extern page *speedButton3;
  extern page *speedButton4;
  extern page *speedButton5;
  extern page *speedButton6;*/

  void erasePage();
  void erasePageHeader();
#endif
