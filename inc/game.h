#pragma once
#include "Menu.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mouseCoord.x = static_cast<float>(x); mouseCoord.y = static_cast<float>(y); }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	vec2 mouseCoord;
	Menu menu;
	MenuType menuType;
	bool inMenu;
	Level level;
	LevelType levelType;
};

}; // namespace Tmpl8