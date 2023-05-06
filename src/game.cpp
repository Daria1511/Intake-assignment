#include "game.h"

namespace Tmpl8
{

	void Game::Init()
	{
		inMenu = true;
		menuType = MenuType::MAIN;
		levelType = LevelType::FIRST;
	}
	void Game::Shutdown() {}


	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// Clamp deltaTime 
		deltaTime = Min( deltaTime, 33.33333333f );
		// convert deltaTime to seconds 
		deltaTime *= 0.001f;

		if (inMenu)
			//It will draw the menu
			menu.UpdateMenu(menuType, screen, mouseCoord, inMenu, levelType);
		else
		{
			//It will draw the levels
			level.UpdateLevel(levelType, screen, deltaTime, inMenu);
			level.UpdateHomeButton(mouseCoord, inMenu, screen);
			menuType = MenuType::MAIN;
		}
	}
}