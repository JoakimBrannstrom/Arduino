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

void setup()
{
	// LcdXY(20,2);
	// LcdWriteString("THE END");

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
	delay(200);

	if(!ballDirectionRight)
		movePaddle(leftPaddle, (leftPaddle.Y + ballSize/2 - ball.Y) < 0);

	if(ballDirectionRight)
		movePaddle(rightPaddle, (rightPaddle.Y + ballSize/2 - ball.Y) < 0);
}

void startGame()
{
	ballDirectionRight = true;
	ballDirectionRight = true;

	ball.X = getDisplayWidth() / 2;
	ball.Y = getDisplayHeight() / 2;

	leftPaddle.X = 0;
	leftPaddle.Y = ball.Y;
	rightPaddle.X = getDisplayWidth() - 2;
	rightPaddle.Y = ball.Y;

	initializeLcd();
	//initializeTimer(&pulse);

	//pulse();
}

void movePaddle(COORD &paddle, bool down)
{
	if(down)
		paddle.Y++;
	else
		paddle.Y--;
}

void pulse()
{
	SetBallPosition();

	clearDisplay();

	drawBall(ball.X, ball.Y);
	drawPaddle(leftPaddle.X, leftPaddle.Y);
	drawPaddle(rightPaddle.X, rightPaddle.Y);
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
	short bigX = x / 4;
	short smallX = x % 4;
	short bigY = y / 8;
	short smallY = y % 8;

	LcdXY(bigX*4+smallX, bigY);
	long data = (0x0001 << ballSize) - 1;
	long smallData = data << smallY;
	byte bigData = smallData >> 8;
	for(int i = smallX; i < smallX + ballSize; i++)
	{
		LcdWriteData(smallData);
	}

	LcdXY(bigX*4+smallX, bigY+1);
	for(int i = smallX; i < smallX + ballSize; i++)
	{
		LcdWriteData(bigData);
	}
}

void drawPaddle(short x, short y)
{
	short bigY = y / 8;
	short smallY = y % 8;

	LcdXY(x, bigY);
	long data = 0xff;
	long smallData = data << smallY;
	byte bigData = smallData >> 8;
	LcdWriteData(smallData);
	LcdWriteData(smallData);

	LcdXY(x, bigY+1);
	LcdWriteData(bigData);
	LcdWriteData(bigData);
}
