#include "Collectables.h"

// DRAW FUNCTIONS
void Collectables::DrawSodaCan(Tmpl8::vec2 & pos, Tmpl8::Surface* screen, float deltaTime)
{
	if (canActive)
	{
		sodaCan.Draw(screen, pos.x, pos.y);
		pos.y += speed * deltaTime;
		CanCollide(pos);
	}
}
void Collectables::DrawSprayCan(Tmpl8::vec2 & pos, Tmpl8::Surface* screen, float deltaTime)
{
	if (canActive)
	{
		sprayCan.Draw(screen, pos.x, pos.y);
		pos.y += speed * deltaTime;
		CanCollide(pos);
	}

}
// CAN COLLIDES WITH THE GROUND
void Collectables::CanCollide(Tmpl8::vec2& pos)
{
	if (pos.y + sodaCan.GetHeight() >= ScreenHeight)
		canActive = 0;

}