#include "windows.h"
#include "Ball.h"

void Ball::BallRespawn()
{
	pos.x = ScreenWidth / 2 - ball.GetWidth()/2;
	pos.y = ScreenHeight - ScreenHeight / 7 - ball.GetHeight();
	dir.x = 0; dir.y = -1.5;
	ballActive = 0;
}

void Ball::MoveBall(float deltaTime)
{
	previousPos = pos;

	//Before ball activation movement
	if (ballActive == 0)
	{
		//if 'A' is pressed
		if (GetAsyncKeyState(0x41))
			// Ball collides left wall
			if (pos.x <= 0+59)
			{
				pos = previousPos;
			}
			// Ball moves to the left
			else
			{
				pos.x -= 2 * speed * deltaTime;
			}

		//if 'D' is pressed
		if (GetAsyncKeyState(0x44))
			// Ball collides right wall
			if (pos.x >= ScreenWidth - ball.GetWidth()-59)
			{
				pos = previousPos;
			}
			// Ball moves to the right
			else
			{
				pos.x += 2 * speed * deltaTime;
			}
	}

	//Ball activation
	if (GetAsyncKeyState(0x20))
	{
		ballActive = 1;
	}

	//Default ball movement + collision with walls
	if (ballActive == 1)
	{
		pos.y += dir.y* speed * deltaTime;
		pos.x += dir.x* speed * deltaTime;
		CollideWall();
	}
}

Tmpl8::vec2 Ball::GetPos() const
{
	return { pos.x + 5,pos.y + 5 };
}
Tmpl8::vec2 Ball::GetPos2() const
{
	return { pos.x - 5 + ball.GetWidth(),pos.y - 5 + ball.GetHeight() };
}

// If the ball collides with the left side of the paddle it will go to the left
void Ball::ChangeDirectionLeft()
{
	pos = previousPos;
	dir.x = -0.7;
	dir.y = -1.5;
}
// If the ball collides with the right side of the paddle it will go to the right
void Ball::ChangeDirectionRight()
{
	pos = previousPos;
	dir.x = 0.7;
	dir.y = -1.5;
}
// If the ball collides with the middle segment of the paddle it will go up
void Ball::ChangeDirectionMiddle()
{
	pos = previousPos;
	dir.x = 0;
	dir.y = -1.5;
}

void Ball::CollideWall()
{
	// Ball collides the top wall
	if (pos.y <= 58)
	{
		pos = previousPos;
		dir.y = -dir.y;
	}
	// Ball collides the left wall
	if (pos.x <= 0)
	{
		pos = previousPos;
		dir.x = -dir.x;
	}
	// Ball collides the right wall
	else if (pos.x >= ScreenWidth - ball.GetWidth())
	{
		pos = previousPos;
		dir.x = -dir.x;
	}
}