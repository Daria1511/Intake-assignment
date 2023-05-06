#pragma once
#include "template.h"
#include "surface.h"
#include "Windows.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "Collectables.h"
#include <cstdlib> // The library that can generate a random number

enum class LevelType
{
	FIRST,
	SECOND,
	THIRD
};

class Level
{
public:

	void UpdateLevel(LevelType& level, Tmpl8::Surface* screen, float deltaTime, bool& inMenu);


	Level():
		paddle(Tmpl8::vec2(ScreenWidth / 2 - 75, ScreenHeight - ScreenHeight / 7)),
		ball(Tmpl8::vec2(ScreenWidth / 2 - 16, ScreenHeight - ScreenHeight / 7 - 32)),
		background(new Tmpl8::Surface("assets/BackAlley.png"), 1),
		menuButton(new Tmpl8::Surface("assets/HomeButton.png"),1),
		menuButton2(new Tmpl8::Surface("assets/HomeButton3.png"), 1),
		lives(new Tmpl8::Surface("assets/TennisBall.png"), 1)
	{};

	~Level()
	{
		for (const auto b : bricks)
		{
			delete b;
		}
	}

	//Check collision between the ball and each brick
	bool checkCollision(Brick* brick, Tmpl8::Surface* screen);

	void CollisionCollectablesPaddle();

	//Paddle Repositioning
	void Restart();
	//Paddle - Ball Collision
	void CollisionBallPaddle();
	//If the home button is pressed will send the player back to the menu
	void UpdateHomeButton(const Tmpl8::vec2& mouse, bool& inMenu, Tmpl8::Surface* screen);
	
	//Levels
	void LoadLevelDefault(Tmpl8::Surface* screen, float deltaTime);
	void LoadLevel1(Tmpl8::Surface* screen, LevelType& level);
	void LoadLevel2(Tmpl8::Surface* screen, LevelType& level);
	void LoadLevel3(Tmpl8::Surface* screen, bool& inMenu);

	void DrawLives(Tmpl8::Surface* screen);
	int GenerateRandomNumber();

private:
	Paddle paddle;
	Ball ball;
	Brick* bricks[24]{nullptr};
	MAP map;
	Collectables can;
	Can canType;

	Tmpl8::Sprite lives;
	Tmpl8::Sprite background;
	Tmpl8::Sprite menuButton;
	Tmpl8::Sprite menuButton2;

	Tmpl8::vec2 pos={0,0}; // brick position

	//the number of rows and colloums of the bricks
	float rows = 0;
	float colloum = 0;

	int livesCounter = 3; // A counter for how many lives are left

	bool initialized = false;   // Determines if the level has been already initialized

	bool dropCollectables = false; // checks if the is already a collectable dropping
	int randomNumber = 0;
	Tmpl8::vec2 canPos = { 0,0 }; //collectable position
	int paddlePowerUpTimer = 0; // a timer for the paddle power-up
};