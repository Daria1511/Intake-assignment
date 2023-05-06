#include "windows.h"
#include "Paddle.h"


void Paddle::RestartPaddle()
{
	if (powerUp)
	{
		pos.x = ScreenWidth / 2 - paddle2.GetWidth()/2;
	}
	else
	{
		pos.x = ScreenWidth / 2 - paddle.GetWidth() / 2;
	}
}

void Paddle::MovePaddle(float deltaTime)
{
	if (powerUp)
	{
		// PowerUp Paddle movement and wall collision

		if (GetAsyncKeyState(0x41))
			if (pos.x <= 0)
				pos.x = 0;
			else
				pos.x -= 2 * speed * deltaTime;

		if (GetAsyncKeyState(0x44))
			if (pos.x >= ScreenWidth - paddle2.GetWidth())
				pos.x = static_cast<float>(ScreenWidth) - paddle2.GetWidth();
			else
				pos.x += 2 * speed * deltaTime;
	}
	else
	{
		// Simple Paddle movement and wall collision

		if (GetAsyncKeyState(0x41))
			if (pos.x <= 0)
				pos.x = 0;
			else
				pos.x -= 2 * speed * deltaTime;

		if (GetAsyncKeyState(0x44))
			if (pos.x >= ScreenWidth - paddle.GetWidth())
				pos.x = static_cast<float>(ScreenWidth) - paddle.GetWidth();
			else
				pos.x += 2 * speed * deltaTime;
	}
}

Tmpl8::vec2 Paddle::GetPos() const
{
	return pos;
}
Tmpl8::vec2 Paddle::GetPos2() const
{
	if (powerUp)
	{
		return { pos.x + paddle2.GetWidth(), pos.y + paddle2.GetHeight() };
	}
	else
	{
		return { pos.x + paddle.GetWidth(),pos.y + paddle.GetHeight() };
	}
}

float Paddle::GetLeft() const 
{
	if (powerUp)
	{
		return pos.x + static_cast<float>(paddle2.GetWidth()) / 4.0f;
	}
	else
	{
		return pos.x + static_cast<float>(paddle.GetWidth()) / 4.0f;
	}
}
float Paddle::GetRight() const 
{
	if (powerUp)
	{
		return pos.x + paddle2.GetWidth() * static_cast<float>(3) / 4.0f;
	}
	else
	{
		return pos.x + paddle.GetWidth() * static_cast<float>(3) / 4.0f;
	}
}