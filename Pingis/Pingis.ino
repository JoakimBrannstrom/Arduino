#include "Timer.h"
#include "Types.h"
#include "PhilipsPCD8544.h"

COORD leftPaddle;
COORD rightPaddle;

const int ballSize = 4;
COORD ball;
bool ballDirectionRight;
bool ballDirectionDown;

long hitCount = 0;
bool gameOver = false;

short bufferPosition = 0;
byte screenBuffer[504];

void setup()
{
	startGame();

	/*
	int x = 0;
	for(int i = 0; i < 48; i++)
	{
		drawBall(x, i);
		x += 4;
	}
	*/
}

void loop()
{
	pulse();
	//delay(20);

	if(hitCount < 6)
	{
		if(!ballDirectionRight)
			movePaddle(leftPaddle, (leftPaddle.Y - ball.Y) < 0);

		if(ballDirectionRight)
			movePaddle(rightPaddle, (rightPaddle.Y - ball.Y) < 0);
	}
}

void startGame()
{
	ballDirectionRight = false;
	ballDirectionDown = true;

	ball.X = getDisplayWidth() / 2;
	ball.Y = getDisplayHeight() / 2;

	leftPaddle.X = 0;
	leftPaddle.Y = ball.Y;
	rightPaddle.X = getDisplayWidth() - 2;
	rightPaddle.Y = ball.Y;

	initializeLcd();
	//initializeTimer(&pulse, 16);

	//pulse();
}

void movePaddle(COORD &paddle, bool down)
{
	if(down)
	{
		if(paddle.Y < getDisplayHeight() - 8)
			paddle.Y++;
	}
	else
	{
		if(paddle.Y > 0)
			paddle.Y--;
	}
}

void pulse()
{
	if(!gameOver)
	{
		SetBallPosition();

		// clearDisplay();
		clearBuffer();

		drawBall(ball.X, ball.Y);
		drawPaddle(leftPaddle.X, leftPaddle.Y);
		drawPaddle(rightPaddle.X, rightPaddle.Y);

		sendBufferToLcd();

		if(leftPaddleMissed())
			GameOver("Winner: Right");
		else if(rightPaddleMissed())
			GameOver("Winner: Left");
	}
}

bool leftPaddleMissed()
{
	if(ball.X < 1)
	{
		short distance = ball.Y - leftPaddle.Y;
		if(distance < 0 || distance > 7)
			return true;

		hitCount++;
	}

	return false;
}

bool rightPaddleMissed()
{
	if(ball.X >= 82)
	{
		short distance = ball.Y - rightPaddle.Y;
		if(distance < 0 || distance > 7)
			return true;

		hitCount++;
	}

	return false;
}

void GameOver(char *winner)
{
	gameOver = true;

	clearDisplay();

	LcdXY(4, 1);
	LcdWriteString(winner);

	LcdXY(18, 3);
	char score[15];
	sprintf(score, "Score: %d", hitCount);
	LcdWriteString(score);
}

void SetBallPosition()
{
	if(ball.X <= 0 || ball.X >= getDisplayWidth() - ballSize)
		ballDirectionRight = !ballDirectionRight;

	if(ball.Y <= 0 || ball.Y >= getDisplayHeight() - ballSize)
		ballDirectionDown = !ballDirectionDown;

	if(ballDirectionRight)
		ball.X += 2;
	else
		ball.X -= 2;

	if(ballDirectionDown)
		ball.Y++;
	else
		ball.Y--;
}

void drawBall(short x, short y)
{
	// drawBlock(x, y, ballSize, ballSize);
	drawBuffer(x, y, ballSize, ballSize);
}

void drawPaddle(short x, short y)
{
	//drawBlock(x, y, 2, 8);
	drawBuffer(x, y, 2, 8);
}

void drawBuffer(short x, short y, short width, short height)
{
	short bigX = x / width;
	short smallX = x % width;
	const int byteSize = 8;
	short bigY = y / byteSize;
	short smallY = y % byteSize;

	// LcdXY(bigX * width + smallX, bigY);
	bufferXY(bigX * width + smallX, bigY);
	long data = (0x0001 << height) - 1;
	long smallData = data << smallY;
	byte bigData = smallData >> 8;
	for(int i = smallX; i < smallX + width; i++)
	{
		//LcdWriteData(smallData);
		bufferWriteData(smallData);
	}

	//LcdXY(bigX * width + smallX, bigY + 1);
	bufferXY(bigX * width + smallX, bigY + 1);
	for(int i = smallX; i < smallX + width; i++)
	{
		// LcdWriteData(bigData);
		bufferWriteData(bigData);
	}
}

void bufferXY(short x, short y)
{
	bufferPosition = x + (y * 84);
}

void bufferWriteData(byte data)
{
	if(0 <= bufferPosition && bufferPosition < 504)
	{
		screenBuffer[bufferPosition] = data;
		bufferPosition++;
	}
}

void sendBufferToLcd()
{
	LcdXY(0, 0);
	
	for(int i = 0; i < 504; i++)
		LcdWriteData(screenBuffer[i]);
}

void clearBuffer()
{
	bufferPosition = 0;
	for(int i = 0; i < 504; i++)
		screenBuffer[i] = 0x00;
}
