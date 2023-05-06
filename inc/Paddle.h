#pragma once
#include "template.h"
#include "surface.h"

class Paddle
{
public:
	Paddle(Tmpl8::vec2& pos1) :
		pos(pos1),
		paddle(new Tmpl8::Surface("assets/Paddle.png"), 1),
		paddle2(new Tmpl8::Surface("assets/Paddle2.png"), 1)
	{
	}

	void DrawPaddle(Tmpl8::Surface* surface)
	{
		if (powerUp)
		{
			paddle2.Draw(surface, pos.x, pos.y);
		}
		else
		{
			paddle.Draw(surface, pos.x, pos.y);
		}
	}

	// Paddle Hitbox
	Tmpl8::vec2 GetPos() const;
	Tmpl8::vec2 GetPos2() const;

	// Paddle divided in 3 segments
	float GetLeft() const;
	float GetRight() const;

	void RestartPaddle();
	void MovePaddle(float deltaTime);
	bool GetPowerUpStatus() const { return powerUp; }
	void SetPowerUpStatus(bool _powerUp) { powerUp = _powerUp; }

private:
	Tmpl8::vec2 pos;
	Tmpl8 ::Sprite paddle;
	Tmpl8::Sprite paddle2;

	float speed = 300;
	bool powerUp = false;
};