// This Arduino example demonstrates bidirectional operation of a
// 28BYJ-48, using a ULN2003 interface board to drive the stepper.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
////////////////////////////////////////////////

// declare variables for the motor pins
int motorXPins[4] = { 8, 9, 10, 11 };
int motorYPins[4] = { 4, 5, 6, 7 };

int sensorXPin = A0;
int sensorXReference = 0;

int sensorYPin = A1;
int sensorYReference = 0;

// int countsperrev = 512;	// number of steps per full revolution
int stepPattern[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };

void setup()
{
	for(int i = 0; i < 4; i++)
	{
		pinMode(motorXPins[i], OUTPUT);
		pinMode(motorYPins[i], OUTPUT);
	}

	sensorXReference = CalibrateSensor(sensorXPin);
	sensorYReference = CalibrateSensor(sensorYPin);

	Serial.begin(9600);
}

int CalibrateSensor(int sensorPin)
{
	delay(10);
	int first = analogRead(sensorPin);
	delay(10);
	int second = analogRead(sensorPin);
	delay(10);
	int third = analogRead(sensorPin);

	return (first + second + third) / 3;
}

void loop()
{
	//return;
	RunMotor(sensorXPin, sensorXReference, motorXPins);
	RunMotor(sensorYPin, sensorYReference, motorYPins);
}

void RunMotor(int sensorPin, int sensorReference, int *motorPins)
{
	int sensorValue = analogRead(sensorPin);
	int motorValue = sensorValue - sensorReference;
	//int motorValue = 0;
	int motorSpeed = abs(motorValue) / 5;
	int sensitivity = 40;

	if(motorValue < -sensitivity)
	{
		motorSpeed = motorSpeed * 1.5;
		anticlockwise(motorSpeed, motorPins);
	}
	else if (motorValue > sensitivity)
		clockwise(motorSpeed, motorPins);
}

void anticlockwise(int motorSpeed, int *motorPins)
{
	for(int i = 0; i < 8; i++)
		stepMotor(i, motorSpeed, motorPins);
}

void clockwise(int motorSpeed, int *motorPins)
{
	for(int i = 7; i >= 0; i--)
		stepMotor(i, motorSpeed, motorPins);
}

void stepMotor(int stepPhase, int motorSpeed, int *motorPins)
{
	setOutput(stepPhase, motorPins);

	// delay between each pin setting (to determine speed)
	int delay = 11000 - (100 * motorSpeed);
	if(delay < 500 || delay > 11000)
		delay = 2000;

	delayMicroseconds(delay);
}

void setOutput(int stepPhase, int *motorPins)
{
	for(int i = 0; i < 4; i++)
	{
		digitalWrite(motorPins[i], bitRead(stepPattern[stepPhase], i));
	}
}
