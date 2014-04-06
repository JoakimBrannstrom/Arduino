//
// This Arduino example demonstrates bidirectional operation of
// two stepper motors.
// We're using a ULN2003 interface board to drive each motor.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
//

#define anticlockwise(stepPhase, motorPins) (setOutput(stepPhase, motorPins))
#define clockwise(stepPhase, motorPins) (setOutput(7 - stepPhase, motorPins))
#define sensitivity 50

// declare variables for the motor pins
int motorXPins[4] = { 4, 5, 6, 7 };
int motorYPins[4] = { 8, 9, 10, 11 };

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

	sensorXReference = CalibrateSensor(sensorXPin, 3) / 3;
	sensorYReference = CalibrateSensor(sensorYPin, 3) / 3;

	Serial.begin(9600);
}

int CalibrateSensor(int sensorPin, int iteration)
{
	if(iteration <= 0)
		return 0;

	delay(10);
	return analogRead(sensorPin) + CalibrateSensor(sensorPin, --iteration);
}

void loop()
{
	//return;
	int motorXDirection = GetMotorDirection(sensorXPin, sensorXReference);
	int motorYDirection = GetMotorDirection(sensorYPin, sensorYReference);

	int delay = 900;

	for(int i = 0; i < 8; i++)
	{
		RunMotor(i, motorXDirection, motorXPins);
		RunMotor(i, motorYDirection, motorYPins);
		delayMicroseconds(delay);
	}
}

int GetMotorDirection(int sensorPin, int sensorReference)
{
	return analogRead(sensorPin) - sensorReference;
}

void RunMotor(int stepPhase, int motorValue, int *motorPins)
{
	if(motorValue < -sensitivity)
		anticlockwise(stepPhase, motorPins);
	else if (motorValue > sensitivity)
		clockwise(stepPhase, motorPins);
}

void setOutput(int stepPhase, int *motorPins)
{
	for(int i = 0; i < 4; i++)
	{
		digitalWrite(motorPins[i], bitRead(stepPattern[stepPhase], i));
	}
}
