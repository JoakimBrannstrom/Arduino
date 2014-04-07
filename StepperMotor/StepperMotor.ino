//
// This Arduino example demonstrates bidirectional operation of
// two stepper motors.
// We're using a ULN2003 interface board to drive each motor.
// The 28BYJ-48 motor is a 4-phase, 8-beat motor, geared down by
// a factor of 68. One bipolar winding is on motor pins 1 & 3 and
// the other on motor pins 2 & 4. The step angle is 5.625/64 and the
// operating Frequency is 100pps. Current draw is 92mA.
//

#define anticlockwise(stepPhase, motor) (setOutput(stepPhase, motor))
#define clockwise(stepPhase, motor) (setOutput(7 - stepPhase, motor))
#define sensitivity 50
#define stepDelayMs 1050

#define NumberOfShiftRegisters 1
#define NumOfRegisterPins NumberOfShiftRegisters * 8

int SerPin = 0;		// to pin 14 on the 75HC595
int RegClkPin = 1;	// to pin 12 on the 75HC595
int SerClkPin = 2;	// to pin 11 on the 75HC595

int sensorXPin = A2;
int sensorYPin = A3;

int sensorXReference = 0;
int sensorYReference = 0;

boolean registers[NumOfRegisterPins];

// int countsperrev = 512;	// number of steps per full revolution
int stepPattern[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };

void setup()
{
	pinMode(SerPin, OUTPUT);
	pinMode(RegClkPin, OUTPUT);
	pinMode(SerClkPin, OUTPUT);

	sensorXReference = CalibrateSensor(sensorXPin, 3) / 3;
	sensorYReference = CalibrateSensor(sensorYPin, 3) / 3;
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

	byte motorX, motorY;
	for(int i = 0; i < 8; i++)
	{
		WriteMotor(i, motorXDirection, &motorX);
		WriteMotor(i, motorYDirection, &motorY);
		RunMotor(motorX, motorY);
	}
}

int GetMotorDirection(int sensorPin, int sensorReference)
{
	return analogRead(sensorPin) - sensorReference;
}

void WriteMotor(int stepPhase, int motorValue, byte *motor)
{
	if(motorValue < -sensitivity)
		anticlockwise(stepPhase, motor);
	else if (motorValue > sensitivity)
		clockwise(stepPhase, motor);
}

void setOutput(int stepPhase, byte *motor)
{
	*motor = stepPattern[stepPhase];
}

void RunMotor(byte motorX, byte motorY)
{
	for(int i = 0; i < 4; i++)
	{
		registers[i] = motorX & (1 << i);
	}

	for(int i = 0; i < 4; i++)
	{
		registers[i+4] = motorY & (1 << i);
	}

	WriteRegisters();
	delayMicroseconds(stepDelayMs);
}

void ClearRegisters()
{
	for(int i = NumOfRegisterPins - 1; i >=  0; i--)
	{
		registers[i] = LOW;
	}
}

void WriteRegisters()
{
	digitalWrite(RegClkPin, LOW);

	for(int i = NumOfRegisterPins - 1; i >=  0; i--)
	{
		digitalWrite(SerClkPin, LOW);

		digitalWrite(SerPin, registers[i]);

		digitalWrite(SerClkPin, HIGH);
	}

	digitalWrite(RegClkPin, HIGH);
}
