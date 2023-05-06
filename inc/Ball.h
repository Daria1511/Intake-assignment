#pragma once

#include "template.h"
#include "surface.h"

class Ball
{
public:
	Ball(const Tmpl8::vec2& pos1) :
		pos(pos1),
		ball(new Tmpl8::Surface("assets/TennisBall.png"), 1),
		dir(0,- 1.5),
		ballActive(0)
	{
		previousPos = pos;
	}

	void DrawBall(Tmpl8::Surface* surface) { ball.Draw(surface, pos.x, pos.y); }

	// Ball position and Hitbox
	Tmpl8::vec2 GetPos() const;
	Tmpl8::vec2 GetPos2() const;

	Tmpl8::vec2 GetPreviousPos() const { return previousPos; }
	void SetPosition(Tmpl8::vec2 _pos) { pos = _pos; }

	// Ball movement and change of direction
	void MoveBall(float deltaTime);
	void ChangeDirectionLeft();
	void ChangeDirectionRight();
	void ChangeDirectionMiddle();

	// Collision between ball and walls
	void CollideWall();
	// Resets all stats of the ball
	void BallRespawn();

	Tmpl8::vec2 GetDirection() {return dir;}
	void SetDirection(Tmpl8::vec2 _dir) {	dir = _dir;}

private:
	Tmpl8::vec2 pos;
	Tmpl8::vec2 previousPos;
	Tmpl8::Sprite ball;
	Tmpl8::vec2 dir;
	float speed=300;
	int ballActive;
};