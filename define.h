#ifndef DEFINE_H_INCLUDED
 #define DEFINE_H_INCLUDED
 //#define DEBUG

 //pin arduino Mega
 #define S1  8
 #define S2  9
 #define S3  10
 #define X3  11
 #define X2  12
 #define X1  13
 #define BP  20
 #define IT0 21
 #define OUT 17
 #define IN 18

 // ==== address eeprom  ====
 #define AD_MAGIC_VALUE       0x00  //  byte
 #define AD_SPEED1_TIMER      0x02  // 4 bytes
 #define AD_SPEED2_TIMER      0x06  // 4 bytes
 #define AD_SPEED3_TIMER      0x0A  // 4 bytes
 #define AD_SPEED4_TIMER      0x0E  // 4 bytes
 #define AD_SPEED5_TIMER      0x12  // 4 bytes
 #define AD_SPEED6_TIMER      0x16  // 4 bytes
 #define AD_PRIME_TIMER       0x1A  // 4 bytes
 #define AD_CLEAN_TIMER       0x1E  // 4 bytes
 #define AD_MORNING_TIMER     0x22  // 4 bytes
 #define AD_NIGHT_TIMER       0x26  // 4 bytes
 #define AD_NO_TIMER          0x2A  // 4 bytes
 #define AD_RPM_SPEED1_TIMER  0x2B  // 1 bytes
 #define AD_RPM_SPEED2_TIMER  0x2C  // 1 bytes
 #define AD_RPM_SPEED3_TIMER  0x2D  // 1 bytes
 #define AD_RPM_SPEED4_TIMER  0x2F  // 1 bytes
 #define AD_RPM_SPEED5_TIMER  0x30  // 1 bytes
 #define AD_RPM_SPEED6_TIMER  0x31  // 1 bytes
 #define AD_RPM_CLEAN_TIMER   0x32  // 1 bytes
 #define AD_BOOST_DELAY       0x33  // 1 bytes
 #define AD_RPM_SPEED1        0x34  // 2 bytes
 #define AD_RPM_SPEED2        0x36  // 2 bytes
 #define AD_RPM_SPEED3        0x38  // 2 bytes
 #define AD_RPM_SPEED4        0x3A  // 2 bytes
 #define AD_RPM_SPEED5        0x3C  // 2 bytes
 #define AD_RPM_SPEED6        0x3E  // 2 bytes
 #define AD_RPM_CLEAN         0x40  // 2 bytes

 #define TIMER_TAB_SIZE 20


 // magic value
 #define MAGIC_VALUE 72
 // screen defintion
 #define SETTING_SCREEN ILI9341_16,38,39,40,41
 #define SETTING_TOUCH 6, 5, 4, 3, 2

 // menu
 #define HOME 1
 #define QUICK_CLEAN 2
 #define PSPEED1 3
 #define PSPEED2 4
 #define SETUP 5
 #define RSPEED1 6
 #define RSPEED2 7
 #define RSPEED3 8
 #define RSPEED4 9
 #define RSPEED5 10
 #define RSPEED6 11
 #define SSPEED1 12
 #define SSPEED2 13
 #define QTSETUP_CLEAN 14
 #define QTSETUP_SPEED1 15
 #define QTSETUP_SPEED2 16
 #define QTSETUP_SPEED3 17
 #define QTSETUP_SPEED4 18
 #define QTSETUP_SPEED5 19
 #define QTSETUP_SPEED6 20
 #define QRSETUP_CLEAN 21
 #define QRSETUP_SPEED1 22
 #define QRSETUP_SPEED2 23
 #define QRSETUP_SPEED3 24
 #define QRSETUP_SPEED4 25
 #define QRSETUP_SPEED5 26
 #define QRSETUP_SPEED6 27
 #define DREMOTE 28
 #define BOOST_PUMP 29
 #define BOOST_DELAY 30
 #define SETUP_2 31
 #define SETUP_RPM_SPEED_PAGE1 32
 #define SETUP_RPM_SPEED_PAGE2 33
 #define SETUP_RPM_SPEED1 34
 #define SETUP_RPM_SPEED2 35
 #define SETUP_RPM_SPEED3 36
 #define SETUP_RPM_SPEED4 37
 #define SETUP_RPM_SPEED5 38
 #define SETUP_RPM_SPEED6 39

 #define ON 1
 #define OFF 0

 #define FORCE_ON 1
 #define FORCE_OFF 0

 // define colors
 #define COLOR_BUTTON VGA_GREEN
 #define LINE_COLOR_BUTTON VGA_WHITE
 #define LINE_COLOR_BUTTON_HIGH VGA_BLUE
 #define BACK_TEXT_BUTTON VGA_GREEN
 #define BACK_TEXT_COLOR VGA_BLACK
 #define TEXT_COLOR VGA_WHITE
 #define LINE_COLOR VGA_BLUE
 #define ERASE_COLOR VGA_BLACK

 // default position button
 #define AXIS_1 35,40,285,76,50
 #define AXIS_2 35,90,285,126,100
 #define AXIS_3 35,140,285,176,150
 #define AXIS_4 35,190,285,226,200

 // default position navigation bar
 #define POS_LEFT  14,185,64,235
 #define POS_MIDDLE 134,185,184,235
 #define POS_RIGHT 255,185,305,235
 #define POS_CENTER 135,85,185,135

 // message detype definition
 #define NO_MESSAGE 100
 #define CLEAN_TIMER_STOPPED 101
 #define SPEED_TIMER_STOPPED 102
 #define CMD_START_CLEAN 103
 #define CMD_START_SPEED1 104
 #define CMD_START_SPEED2 105
 #define CMD_START_SPEED3 106
 #define CMD_START_SPEED4 107
 #define CMD_START_SPEED5 108
 #define CMD_START_SPEED6 109
 #define CMD_STOP_PUMP 110
 #define CHECK_INPUT_VALUES 111
 #define BOOST_ON 112
 #define BOOST_OFF 113


// rpm value
 #define NO_RPM       0000
 #define RPM_CLEAN    3250
 #define RPM_SPEED1   1300
 #define RPM_SPEED2   1600
 #define RPM_SPEED3   1800
 #define RPM_SPEED4   2200
 #define RPM_SPEED5   2900
 #define RPM_SPEED6   3000

 #define RPM_REMOTE   0000

 #define RPM_MAX 3250
 #define RPM_MIN 600
 // rpm ID
 #define NO_RPM_ID       0
 #define RPM_SPEED1_ID   1
 #define RPM_SPEED2_ID   2
 #define RPM_SPEED3_ID   3
 #define RPM_SPEED4_ID   4
 #define RPM_SPEED5_ID   5
 #define RPM_SPEED6_ID   6
 #define RPM_CLEAN_ID   7

 #define RPM_REMOTE   0000

 #define MAX_RPM 7

 // timers
 #define NO_T 0
 #define SPEED1 1
 #define SPEED2 2
 #define SPEED3 3
 #define SPEED4 4
 #define SPEED5 5
 #define SPEED6 6
 #define CLEAN 7
 #define MORNING 8
 #define NIGHT 9
 #define REMOTE 10

// timer value
 #define NO_TIMER NO_T,0,0,0
 #define MORNING_TIMER MORNING,6,0,0
 #define NIGHT_TIMER NIGHT,6,0,0
 #define SPEED1_TIMER SPEED1,0,30,0
 #define SPEED2_TIMER SPEED2,0,30,0
 #define SPEED3_TIMER SPEED3,0,30,0
 #define SPEED4_TIMER SPEED4,0,30,0
 #define SPEED5_TIMER SPEED5,0,30,0
 #define SPEED6_TIMER SPEED6,0,30,0
 #define CLEAN_TIMER CLEAN,0,30,00

 // booster pump delay sec
 #define BOOST_DELAY_VAL   10

#endif
