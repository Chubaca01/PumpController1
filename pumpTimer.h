#ifndef PUMPTIMER_H_INCLUDED
  #define PUMPTIMER_H_INCLUDED
  class pumpTimer {
    public:
      unsigned char hour[20];
      unsigned char mn[20];
      unsigned char sec[20];
      unsigned char hourMod[20];
      unsigned char mnMod[20];
      unsigned char secMod[20];
      unsigned char stat[20];
      int currentTimer;
      pumpTimer(void){currentTimer=0;};
      void init(unsigned char cur, char h,char m,char s){currentTimer=cur;hour[cur]=h;mn[cur]=m;sec[cur]=s;stat[cur]=0;};
      void initModVal(int cur){hourMod[cur]=hour[cur];mnMod[cur]=mn[cur];secMod[cur]=sec[cur];};
      void start(int timer){stat[timer]=1;};
      void stop(int timer){stat[timer]=0;};
      int dec(int timer);
      void saveTimer(char addr,int timer);
      void hourUp(int timer);
      void hourDown(int timer);
      void minUp(int timer);
      void minDown(int timer);
      void secUp(int timer);
      void secDown(int timer);
      void setCurrentTimer(int cur){currentTimer=cur;}
  };

  extern pumpTimer *runningTimer;
  void updateTimer(void);
  void startTimer(char curTimer);
  void stopTimer(char curTimer);
#endif
