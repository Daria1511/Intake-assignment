#include "Brick.h"

// Chose the brick state and draws it
void Brick::DrawBrick(Tmpl8::Surface* surface)
{
	switch (state)
	{
	case State::WOKIA:
		wokia->Draw(surface, pos.x, pos.y); 
		break;
	case State::HIT1: 
		brick1->Draw(surface, pos.x, pos.y); 
		break;
	case State::HIT2: 
		brick2->Draw(surface, pos.x, pos.y);
		break;
	default: break; // we don't draw here
	}


}

// Changes the state of the brick depending on it's type
bool Brick::ChangeState()
{
	if (state == State::HIT1)
	{
		state = State::NOTHING;
		return true;
	}
	else if (state == State::HIT2)
	{
		state = State::HIT1;
		return true;
	}
	return false;
}