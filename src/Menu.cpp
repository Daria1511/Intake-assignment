#include "Menu.h"
#include "SDL.h"


// SWITCHES THE MENUS
void Menu::UpdateMenu(MenuType& menu, Tmpl8::Surface* screen, const Tmpl8::vec2& mouse, bool& inMenu, LevelType& level)
{
	switch (menu)
	{
	case MenuType::MAIN:
		UpdateMainMenu(screen, mouse, menu);
		break;
	case MenuType::LEVELS:
		UpdateLevelsMenu(screen, mouse, menu, inMenu, level);
		break;
	case MenuType::CONTROLS:
		UpdateControlsMenu(screen, mouse, menu);
		break;
	default:
		break;
	}

	mousePressedLastFrame = GetAsyncKeyState(VK_LBUTTON);
}


//MAIN MENU
void Menu::DrawMainMenu(Tmpl8::Surface* screen)
{
	menuBackground.Draw(screen, 0, 0);
	levelsButton1.Draw(screen, 95, 300);
	controlsButton1.Draw(screen, 95, 400);
	exitButton1.Draw(screen, 95, 500);
}
void Menu::UpdateMainMenu(Tmpl8::Surface* screen, const Tmpl8::vec2& mouse, MenuType& menu)
{
	//DRAW THE MAIN MENU
	DrawMainMenu(screen);
	bool mouseButtonPressed = !mousePressedLastFrame && GetAsyncKeyState(VK_LBUTTON);

	//MOUSE IS HOVERING THE LEVEL BUTTON
	if ((mouse.y >= 300 && mouse.y <= 388) && (mouse.x >= 95 && mouse.x <= 559))
	{
		levelsButton2.Draw(screen, 95, 300);
		// GO TO LEVELS MENU
		if (mouseButtonPressed)
			menu = MenuType::LEVELS;
	}

	//MOUSE IS HOVERING THE CONTROLS BUTTON
	else if ((mouse.y >= 400 && mouse.y <= 488) && (mouse.x >= 95 && mouse.x <= 559))
	{
		controlsButton2.Draw(screen, 95, 400);
		// GO TO CONTROLS MENU
		if (mouseButtonPressed)
			menu = MenuType::CONTROLS;
	}

	//MOUSE IS HOVERING THE EXIT BUTTON
	else if ((mouse.y >= 500 && mouse.y <= 588) && (mouse.x >= 95 && mouse.x <= 559))
	{
		exitButton2.Draw(screen, 95, 500);
		// EXIT THE GAME
		if (mouseButtonPressed)
		{
			SDL_Event e{};
			e.type = SDL_QUIT;
			SDL_PushEvent(&e);
		}
	}

}

// LEVELS MENU
void Menu::DrawLevelsMenu(Tmpl8::Surface* screen)
{
	levelsMenu.Draw(screen, 0, 0);
	button1A.Draw(screen, 50, 200);
	button2A.Draw(screen, ScreenWidth / 2 - 44, 200);
	button3A.Draw(screen, 500, 200);
	homeButton1.Draw(screen, ScreenWidth / 2 - 50, ScreenHeight * 3 / 4);
}
void Menu::UpdateLevelsMenu(Tmpl8::Surface* screen, const Tmpl8::vec2& mouse, MenuType& menu, bool& inMenu, LevelType& level)
{
	// DRAW THE LEVELS MENU
	DrawLevelsMenu(screen);
	bool mouseButtonPressed = GetAsyncKeyState(VK_LBUTTON);

	//MOUSE IS HOVERING LEVEL1 BUTTON
	if ((mouse.y >= 200 && mouse.y <= 288) && (mouse.x >= 50 && mouse.x <= 138))
	{
		button1B.Draw(screen, 50, 200);
		// GO TO LEVEL 1
		if (mouseButtonPressed)
		{
			level = LevelType::FIRST;
			inMenu = false;
		}
	}

	//MOUSE IS HOVERING LEVEL2 BUTTON
	if ((mouse.y >= 200 && mouse.y <= 288) && (mouse.x >= ScreenWidth / 2 - 44 && mouse.x <= ScreenWidth / 2 + 44))
	{
		button2B.Draw(screen, ScreenWidth / 2 - 44, 200);
		// GO TO LEVEL 2
		if (mouseButtonPressed)
		{
			level = LevelType::SECOND;
			inMenu = false;
		}
	}

	//MOUSE IS HOVERING LEVEL3 BUTTON
	if ((mouse.y >= 200 && mouse.y <= 288) && (mouse.x >= 500 && mouse.x <= 588))
	{
		button3B.Draw(screen, 500, 200);
		// GO TO LEVEL 3
		if (mouseButtonPressed)
		{
			level = LevelType::THIRD;
			inMenu = false;
		}
	}

	//MOUSE IS HOVERING HOME BUTTON
	if ((mouse.y >= static_cast<float>(ScreenHeight * 3) / 4 && mouse.y <= ScreenHeight * 3 / 4 + 100) && (mouse.x >= ScreenWidth / 2 - 50 && mouse.x <= ScreenWidth / 2 + 50))
	{
		homeButton2.Draw(screen, ScreenWidth / 2 - 50, ScreenHeight * 3 / 4);
		// GO BACK TO THE MAIN MENU
		if (mouseButtonPressed)
			menu = MenuType::MAIN;
	}
}


// CONTROLS MENU
void Menu::DrawControlsMenu(Tmpl8::Surface* screen)
{
	controlsMenu.Draw(screen, 0, 0);
	homeButton1.Draw(screen, ScreenWidth / 2 - 50, ScreenHeight * 3 / 4);
}
void Menu::UpdateControlsMenu(Tmpl8::Surface* screen, const Tmpl8::vec2& mouse, MenuType& menu)
{
	// DRAW THE CONTROLS MENU
	DrawControlsMenu(screen);
	bool mouseButtonPressed = !mousePressedLastFrame && GetAsyncKeyState(VK_LBUTTON);

	//MOUSE IS HOVERING HOME BUTTON
	if ((mouse.y >= static_cast<float>(ScreenHeight * 3) / 4 && mouse.y <= ScreenHeight * 3 / 4 + 100) && (mouse.x >= ScreenWidth / 2 - 50 && mouse.x <= ScreenWidth / 2 + 50))
	{
		homeButton2.Draw(screen, ScreenWidth / 2 - 50, ScreenHeight * 3 / 4);
		// GO BACK TO THE MAIN MENU
		if (mouseButtonPressed)
			menu = MenuType::MAIN;
	}
}