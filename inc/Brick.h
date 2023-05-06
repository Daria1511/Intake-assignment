#pragma once
#include "template.h"
#include "surface.h"
#include <memory>

// STATES OF BRICKS
enum class State
{
	NOTHING,    // Literally nothing
	WOKIA,      // It stand for wanna be nokia
	HIT2,       // The brick that needs 2 hits to be destroyed
	HIT1        // The brick that needs 1 hit to be destroyed
};

// LEVEL LAYOUTS
struct MAP
{
	// First level layout
	State level1[24] = { State::HIT1,State::HIT1, State::HIT1, State::HIT1, State::HIT1, State::HIT1,
						State::HIT1,State::HIT1, State::HIT1, State::HIT1, State::HIT1, State::HIT1,
						State::NOTHING,State::HIT1, State::HIT1, State::HIT1, State::HIT1, State::NOTHING,
						State::NOTHING,State::NOTHING, State::HIT1, State::HIT1, State::NOTHING, State::NOTHING };
	// Second level layout
	State level2[24] = { State::NOTHING,State::NOTHING, State::HIT2, State::HIT1, State::NOTHING, State::NOTHING,
						State::NOTHING,State::HIT2, State::HIT1, State::HIT2, State::HIT1, State::NOTHING,
						State::HIT2,State::HIT1, State::HIT2, State::HIT1, State::HIT2, State::HIT1,
						State::HIT1,State::HIT2, State::HIT1, State::HIT2, State::HIT1, State::HIT2 };
	// Third level layout
	State level3[24] = { State::WOKIA,State::HIT1, State::HIT2, State::HIT2, State::HIT1, State::WOKIA,
						State::WOKIA,State::HIT1, State::HIT2, State::HIT2, State::HIT1, State::WOKIA,
						State::WOKIA,State::HIT1, State::HIT1, State::HIT1, State::HIT1, State::WOKIA,
						State::WOKIA,State::NOTHING, State::NOTHING, State::NOTHING, State::NOTHING, State::WOKIA };
};

class Brick
{
public:
	Brick(std::shared_ptr<Tmpl8::Sprite> _wokia,
		std::shared_ptr<Tmpl8::Sprite> _brick1,
		std::shared_ptr<Tmpl8::Sprite> _brick2,
		Tmpl8::vec2 _hitbox, State _state) :
		wokia(std::move(_wokia)),
		brick1(std::move(_brick1)),
		brick2(std::move(_brick2))
	{
		state = _state;
		pos = _hitbox;
	}

	// Picks which type of brick to draw
	void DrawBrick(Tmpl8::Surface* surface);

	// Position and Hitbox management
	Tmpl8::vec2 GetPos() const { return pos; }
	Tmpl8::vec2 GetPos2() const { return { pos.x + wokia->GetWidth() ,pos.y + wokia->GetHeight() }; }
	void SetHitBox(Tmpl8::vec2 _pos) { pos = _pos; }
	
	// State management
	State GetState() const { return state; }
	void SetState(State _state) { state = _state; }
	bool ChangeState();

private:
	std::shared_ptr<Tmpl8::Sprite> wokia;
	std::shared_ptr<Tmpl8::Sprite> brick1;
	std::shared_ptr<Tmpl8::Sprite> brick2;
	Tmpl8::vec2 pos;
	State state = State::NOTHING;
};