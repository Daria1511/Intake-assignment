#pragma once
#include "template.h"
#include "surface.h"

// Types of cans
enum class Can
{
	SODA,
	SPRAY
};

class Collectables
{
public:
	Collectables() :
		sodaCan(new Tmpl8::Surface("assets/Soda Can.png"), 1),
		sprayCan(new Tmpl8::Surface("assets/Spray Can.png"), 1)
	{};
	
	// Draw cans functions
	void DrawSodaCan(Tmpl8::vec2 & pos, Tmpl8::Surface* screen, float deltaTime);
	void DrawSprayCan(Tmpl8::vec2 & pos, Tmpl8::Surface* screen, float deltaTime);

	// Check if the can collides with the ground and if it does it won't draw it anymore
	void CanCollide(Tmpl8::vec2& pos);

	// Can activity management
	void SetCanActive(bool _canActive) { canActive = _canActive; }
	bool GetCanActive() const { return canActive; }

	// Can positions
	float GetPosX2(Tmpl8::vec2& pos) { return pos.x + sodaCan.GetWidth(); }
	float GetPosY2(Tmpl8::vec2& pos) { return pos.y + sodaCan.GetHeight(); }

private:
	Tmpl8::Sprite sodaCan;
	Tmpl8::Sprite sprayCan;
	float speed = 300;
	// The variable "canActive" starts the collectable drop
	bool canActive = false;
};