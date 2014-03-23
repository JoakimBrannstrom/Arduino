#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Uno
#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void startGame();
void movePaddle(COORD &paddle, bool down);
void pulse();
bool leftPaddleMissed();
bool rightPaddleMissed();
void GameOver(char *winner);
void SetBallPosition();
void drawBall(short x, short y);
void drawPaddle(short x, short y);
void drawBuffer(short x, short y, short width, short height);
void bufferXY(short x, short y);
void bufferWriteData(byte data);
void sendBufferToLcd();
void clearBuffer();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\Pingis.ino"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\Font.h"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\PhilipsPCD8544.cpp"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\PhilipsPCD8544.h"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\Timer.cpp"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\Timer.h"
#include "D:\Dropbox\Dev\Git\Arduino\Pingis\Types.h"
#endif
