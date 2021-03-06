#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Leonardo
#define __AVR_ATmega32u4__
#define __AVR_ATmega32U4__
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
int CalibrateSensor(int sensorPin, int iteration);
//
int GetMotorDirection(int sensorPin, int sensorReference);
void WriteMotor(int stepPhase, int motorValue, byte *motor);
void setOutput(int stepPhase, byte *motor);
void RunMotor(byte motorX, byte motorY);
void ClearRegisters();
void WriteRegisters();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\leonardo\pins_arduino.h" 
#include "D:\Dropbox\Dev\Git\Arduino\StepperMotor\StepperMotor.ino"
#include "D:\Dropbox\Dev\Git\Arduino\StepperMotor\StepperMotor2.ino"
#endif
