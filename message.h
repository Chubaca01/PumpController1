#ifndef MESSAGE_H_INCLUDED
 #define MESSAGE_H_INCLUDED

 class message {
    char  mes;
    int isMes;
   public:
   message(void){mes=0; isMes = 0;};
   void sendMessage(char t){mes=t;isMes = 1;};
   int isMessage(void);
   char getMessage(void){isMes = 0;return mes;};
   void clearMessage(void){mes=0;isMes =  0;}
 };


 extern message *cMessage;
 extern message *pumpMessage;
 extern message *sMessage;
 extern message *boostMessage;

 void sendMessageTimerStop(char curTimer);
 void sendPumpMessage(char curTimer);
#endif
