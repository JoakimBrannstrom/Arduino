/*
Blinkenlights
=============
Switches between a number of different modes of how the leds should light up
*/

// avr-libc library includes
#include <avr/io.h>
#include <avr/interrupt.h>

#define FIRSTMODE 0
#define LASTMODE 4
const int minLed = 9;
const int maxLed = 13;

int previousLed;
int currentLed;
int nextLed;
bool up;

int mode = FIRSTMODE;
int timerCount = 0;

void reset()
{
	timerCount = 0;

	previousLed = minLed;
	currentLed = minLed;
	nextLed = minLed;
	up = true;

	turnOffAllLeds();
}

void setup()
{
	// initialize the digital pins as an output.
	for(int i = minLed; i <= maxLed; i++)
		pinMode(i, OUTPUT);

	initializeTimer();
	reset();
}

void loop()
{
	switch(mode)
	{
		case 0:
			nightRider();
			break;
		case 1:
			flash();
			break;
		case 2:
			roll();
			break;
		case 3:
			rollInTheMiddle();
			break;
		case 4:
			lightInTheMiddle();
			break;
	}
}

void nightRider()
{
	up = goUp(currentLed);

	digitalWrite(currentLed, LOW);

	currentLed = nextPin(currentLed);

	digitalWrite(currentLed, HIGH);

	delay(100);
}

void flash()
{
	up = goUp(currentLed);

	blink(currentLed);
	blink(currentLed);
	blink(currentLed);

	currentLed = nextPin(currentLed);
}

void blink(int pin)
{
	digitalWrite(pin, HIGH);
	delay(50);
	digitalWrite(pin, LOW);
	delay(50);
}

void roll()
{
	digitalWrite(previousLed, LOW);
	//digitalWrite(currentLed, LOW);

	previousLed = currentLed;
	currentLed = nextLed;

	nextLed++;
	if(nextLed > maxLed+2)
		nextLed = minLed;

	digitalWrite(nextLed, HIGH);

	delay(120);
}

void rollInTheMiddle()
{
	int offset = currentLed - minLed;

	int lowLed = minLed + offset;
	int highLed = maxLed - offset;

	currentLed++;
	if(currentLed > maxLed)
		currentLed = minLed;

	turnOffAllLeds();

	digitalWrite(lowLed, HIGH);
	digitalWrite(highLed, HIGH);

	delay(120);
}

bool turnOn = false;
void lightInTheMiddle()
{
	int offset = currentLed - minLed;

	int lowLed = minLed + offset;
	int highLed = maxLed - offset;

	currentLed++;
	if(currentLed > maxLed)
	{
		turnOn = !turnOn;
		currentLed = minLed;
	}

	if(turnOn)
	{
		digitalWrite(lowLed, HIGH);
		digitalWrite(highLed, HIGH);
	}
	else
	{
		digitalWrite(lowLed, LOW);
		digitalWrite(highLed, LOW);
	}

	delay(80);
}

bool goUp(int pin)
{
	if(pin <= minLed)
		return true;
	else if(pin >= maxLed)
		return false;

	return up;
}

int nextPin(int pin)
{
	if(up)
		return ++pin;
	else
		return --pin;
}

void turnOffAllLeds()
{
	for(int i = minLed; i <= maxLed; i++)
		digitalWrite(i, LOW);
}

int getTimerCountForOneSecond()
{
	// (target time) = (timer resolution) * (# timer counts + 1)
	// => (# timer counts + 1) = (target time) / (timer resolution)
	// => (# timer counts + 1) = (1 s) / (1 / (clock frequency / prescaler))
	// => (# timer counts + 1) = (clock frequency / prescaler)
	// => (# timer counts + 1) = (16*10^6 / 1024)
	// => (# timer counts + 1) = 15625

	// 16MHz
	return 15625 - 1;	// leave one clock cycle, it's needed by the timer when resetting itself to zero
}

void initializeTimer()
{
	// http://www.engblaze.com/microcontroller-tutorial-avr-and-arduino-timer-interrupts/

	// initialize Timer1
	cli();			// disable global interrupts
	TCCR1A = 0;		// set entire TCCR1A register to 0
	TCCR1B = 0;		// same for TCCR1B
 
	// set compare match register to desired timer count:
	//OCR1A = 15624;
	OCR1A = getTimerCountForOneSecond();

	// turn on CTC mode:
	TCCR1B |= (1 << WGM12);

	// Set CS10 and CS12 bits for 1024 prescaler:
	TCCR1B |= (1 << CS10);
	TCCR1B |= (1 << CS12);

	// enable timer compare interrupt:
	TIMSK1 |= (1 << OCIE1A);

	// enable global interrupts:
	sei();
}

ISR(TIMER1_COMPA_vect)
{	// This function will trigger on timer-interupts
	timerCount++;

	if(timerCount >= LASTMODE)
	{
		reset();

		int nextMode = mode+1;
		if(nextMode > LASTMODE)
			nextMode = FIRSTMODE;

		mode = nextMode;
	}
}
