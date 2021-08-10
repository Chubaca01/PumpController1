#ifndef PAGES_H_INCLUDED
  #define PAGES_H_INCLUDED
  class pageObject {
      char tText[50];
      char *text;
      int posx1,posx2,posy1,posy2,post;
      int isBitmap;
      int isblink;

    public:
    unsigned char boostDelay;
    unsigned char boostDelayMod;
    char rpm[10];
    char rpmMod[10];
    int rpmTab[10];
    int curRemoteRpm;
    // constructor button
    pageObject(char *t,int px1,int py1,int px2,int py2,int px3){strcpy(tText,t);text=&tText[0];posx1=px1;posy1=py1;posx2=px2;posy2=py2;post=px3;isBitmap=0;isblink=0;}
    // constructor header
    pageObject(char *t,int px1,int py1){strcpy(tText,t);text=&tText[0];post=px1;posy1=py1;isBitmap=0;isblink=0;}
    // constructor text
    pageObject(int px1,int py1){text=&tText[0];post=px1;posy1=py1;isBitmap=0;isblink=0;}
    // constructor navigation bar
    pageObject(int px1,int py1,int px2,int py2){text=&tText[0];posx1=px1;posy1=py1;posx2=px2;posy2=py2;isBitmap=1;isblink=0;};
    void initRpm(unsigned char cur,char rpmVal){rpm[cur]=rpmVal;rpmMod[cur]=rpmVal;curRemoteRpm=0;};
    void initModVal(int cur){rpmMod[cur]=rpm[cur];};
    void rpmUp(int cur);
    void rpmDown(int cur);
    void initBoostDelay(char boostVal){boostDelay= boostVal; boostDelayMod = boostVal;};
    void initModBoost(void){boostDelayMod = boostDelay;}
    void boostUp(void);
    void boostDown(void);
    void saveBoostDelay(char addr);
    unsigned int getboostDelay(void){unsigned int val; val = boostDelay*1000;return val;};
    void saveRpm(char addr,int timer);
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

  void erasePage();
  void erasePageHeader();
#endif
