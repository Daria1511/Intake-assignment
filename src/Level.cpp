#include "Level.h"
#include <memory>
#include<iostream>

std::shared_ptr<Tmpl8::Sprite> brick1_sprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/Brick1.png"), 1);
std::shared_ptr<Tmpl8::Sprite> brick2_sprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/Brick2.png"), 1);
std::shared_ptr<Tmpl8::Sprite> wokia_sprite = std::make_shared<Tmpl8::Sprite>(new Tmpl8::Surface("assets/Wokia.png"), 1);

// SWITCH THE LEVELS
void Level::UpdateLevel(LevelType& level, Tmpl8::Surface* screen, float deltaTime, bool& inMenu)
{
	LoadLevelDefault(screen, deltaTime);

	switch (level)
	{
	case LevelType::FIRST:
		LoadLevel1(screen, level);
		break;
	case LevelType::SECOND:
		LoadLevel2(screen, level);
		break;
	case LevelType::THIRD:
		LoadLevel3(screen, inMenu);
		break;
	default:
		break;
	}
}

// PLACE PADDLE IN THE INITIAL POSITION
void Level::Restart()
{
	can.SetCanActive(false);
	paddle.RestartPaddle();
	ball.BallRespawn();
}

// CHECK COLLISION BETWEEN THE BALL AND THE PADDLE
void Level::CollisionBallPaddle()
{

	if (ball.GetPos2().y >= paddle.GetPos().y && ball.GetPos().y <= paddle.GetPos().y + 1)
	{
		// BALL HITS THE LEFT SEGMENT OF THE PADDLE
		if (ball.GetPos().x > paddle.GetPos().x && ball.GetPos().x < paddle.GetLeft()
			|| ball.GetPos2().x > paddle.GetPos().x && ball.GetPos2().x < paddle.GetLeft())
		{
			// CHANGES THE DIRECTION OF THE BALL TO LEFT
			ball.ChangeDirectionLeft();
		}

		// BALL HITS THE RIGHT SEGMENT OF THE PADDLE
		else if (ball.GetPos().x > paddle.GetRight() && ball.GetPos().x < paddle.GetPos2().x
			|| ball.GetPos2().x > paddle.GetRight() && ball.GetPos2().x < paddle.GetPos2().x)
		{
			// CHANGES THE DIRECTION OF THE BALL TO RIGHT
			ball.ChangeDirectionRight();
		}

		// BALL HITS THE MIDDLE SEGMENT OF THE PADDLE
		else if (ball.GetPos().x >= paddle.GetLeft() && ball.GetPos().x <= paddle.GetRight()
			|| ball.GetPos2().x <= paddle.GetLeft() && ball.GetPos2().x >= paddle.GetRight())
		{
			// THE BALL MOVES ONLY UPWARDS
			ball.ChangeDirectionMiddle();
		}
	}
}

// CHECK COLLISION BETWEEN THE CANS AND THE PADDLE
void Level::CollisionCollectablesPaddle()
{
	if ((canPos.y >= paddle.GetPos().y && canPos.y <= paddle.GetPos2().y) ||
		(can.GetPosY2(canPos) <= paddle.GetPos2().y && can.GetPosY2(canPos)>=paddle.GetPos().y))
	{
		if ((canPos.x > paddle.GetPos().x && canPos.x < paddle.GetPos2().x) ||
			(can.GetPosX2(canPos) < paddle.GetPos2().x && can.GetPosX2(canPos) > paddle.GetPos().x))
		{
			can.SetCanActive(false);

			// The soda power-up makes the paddle bigger
			if (canType == Can::SODA)
			{
				// Initialize the power-up timer
				paddlePowerUpTimer = 1000;
				paddle.SetPowerUpStatus(true);
			}
			// The spray power-up gives the player another life
			else if (canType == Can::SPRAY)
			{
				// Add a life only if you don't have maximum lives
				if (livesCounter < 3) livesCounter++;
			}
		}
	}
}

// GENERATE A RANDOM NUMBER BETWEEN 0 AND 99
int Level::GenerateRandomNumber()
{
	return rand() % 100;
}

// CHECK COLLISION BETWEEN THE BALL AND THE BRICKS AND DROP POWER-UP
bool Level::checkCollision(Brick* brick, Tmpl8::Surface* screen)
{
	bool collided = false;

	// BALL HITS BRICK FROM THE RIGHT
	if (ball.GetPos().x <= brick->GetPos2().x && ball.GetPos().x >= brick->GetPos2().x - 3)
	{
		// BALL HITS THE CORNER OF THE BRICK
		if ((ball.GetPos2().y <= brick->GetPos().y + 3 && ball.GetPos2().y >= brick->GetPos().y) ||
			(ball.GetPos().y <= brick->GetPos2().y && ball.GetPos().y >= brick->GetPos2().y-3))
		{
			// IF THE BRICK EXISTS IT WILL COLLIDE
			if (brick->GetState() != State::NOTHING)
			{
				ball.SetDirection(-ball.GetDirection());
				collided = true;
			}
		}
		// BALL HITS THE SIDE OF THE BRICK
		else if((ball.GetPos().y >= brick->GetPos().y && ball.GetPos().y < brick->GetPos2().y - 3) ||
			(ball.GetPos2().y <= brick->GetPos2().y && ball.GetPos2().y > brick->GetPos().y))
		{
			// IF THE BRICK EXISTS IT WILL COLLIDE
			if (brick->GetState() != State::NOTHING)
			{
				ball.SetDirection({ -ball.GetDirection().x, ball.GetDirection().y });
				collided = true;
			}
		}
	}
	// BALL HITS BRICK FROM THE LEFT
	else if (ball.GetPos2().x >= brick->GetPos().x && ball.GetPos2().x <= brick->GetPos().x + 3)
	{
		// BALL HITS THE CORNER OF THE BRICK
		if ((ball.GetPos2().y <= brick->GetPos().y + 3 && ball.GetPos2().y >= brick->GetPos().y) ||
			(ball.GetPos().y <= brick->GetPos2().y && ball.GetPos().y >= brick->GetPos2().y - 3))
		{
			// IF THE BRICK EXISTS IT WILL COLLIDE
			if (brick->GetState() != State::NOTHING)
			{
				ball.SetDirection(-ball.GetDirection());
				collided = true;
			}
		}
		// BALL HITS THE SIDE OF THE BRICK
		else if ((ball.GetPos().y >= brick->GetPos().y && ball.GetPos().y < brick->GetPos2().y - 3) ||
			(ball.GetPos2().y <= brick->GetPos2().y && ball.GetPos2().y > brick->GetPos().y))
		{
			// IF THE BRICK EXISTS IT WILL COLLIDE
			if (brick->GetState() != State::NOTHING)
			{
				ball.SetDirection({ -ball.GetDirection().x, ball.GetDirection().y });
				collided = true;
			}
		}
	}
	// BALL HITS BRICK FROM BELLOW OR ABOVE
	else if ((ball.GetPos().x >= brick->GetPos().x && ball.GetPos().x < brick->GetPos2().x - 3) ||
		(ball.GetPos2().x > brick->GetPos().x + 3 && ball.GetPos2().x <= brick->GetPos2().x))
	{
		if ((ball.GetPos2().y <= brick->GetPos().y + 3 && ball.GetPos2().y >= brick->GetPos().y) ||
			(ball.GetPos().y <= brick->GetPos2().y && ball.GetPos().y >= brick->GetPos2().y - 3))
		{
			// IF THE BRICK EXISTS IT WILL COLLIDE
			if (brick->GetState() != State::NOTHING)
			{
				ball.SetDirection({ ball.GetDirection().x, -ball.GetDirection().y });
				collided = true;
			}
		}
	}
	if(collided)
	{
		// IF THE BALL COLLIDES WITH THE BRICK IT WILL CHANGE IT'S STATE
		if (brick->ChangeState())
		{
			// When a brick has changed it's state there is a posibility to drop a power-up if one is not already dropping
			if (!can.GetCanActive())
			{
				randomNumber = GenerateRandomNumber();

				// There will be a probability of 20% to drop a soda power-up
				// The soda power-up makes the paddle bigger
				if (randomNumber % 4 == 0 && randomNumber % 5 != 0)
				{
					// set the start falling position of the can
					canPos = brick->GetPos();
					can.SetCanActive(true);
					canType = Can::SODA;
				}
				// There will be probability of 15% to drop a spray power-up
				// The spray power-up gives the player another life
				else if (randomNumber % 5 == 0 && randomNumber % 4 != 0)
				{
					// set the start falling position of the can
					canPos = brick->GetPos();
					can.SetCanActive(true);
					canType = Can::SPRAY;
				}
			}
		}
		ball.SetPosition(ball.GetPreviousPos());
	}
	return collided;
}

// CHECK IF THE MOUSE HOVERS THE HOMEBUTTON AND IF CLICKED ENTERS THE MENU RESETING THE LEVEL
void Level::UpdateHomeButton(const Tmpl8::vec2& mouse, bool& inMenu, Tmpl8::Surface* screen)
{
	bool mouseButtonPressed = GetAsyncKeyState(VK_LBUTTON);
	// Check if the mouse hovers the home button
	if ((mouse.y >= 4 && mouse.y <= 54) && (mouse.x >= 4 && mouse.x <= 54))
	{
		menuButton2.Draw(screen, 4, 4);
		// Check if the mouse button is pressed, if true it will enter the menu
		if (mouseButtonPressed)
		{
			inMenu = true;
			Restart();
			initialized = false;
		}
	}
}

// LOAD ALL THE COMMON FUNCTIONS IN THE LEVELS
void Level::LoadLevelDefault(Tmpl8::Surface* screen, float deltaTime)
{
	// Movement functions
	ball.MoveBall(deltaTime);
	paddle.MovePaddle(deltaTime);

	//Draw functions
	background.Draw(screen, 0, 0);
	DrawLives(screen);
	ball.DrawBall(screen);
	paddle.DrawPaddle(screen);
	menuButton.Draw(screen, 4, 4);
	if (can.GetCanActive())
	{
		if (canType == Can::SODA)
		{
			can.DrawSodaCan(canPos, screen, deltaTime);
		}
		else if (canType == Can::SPRAY)
		{
			can.DrawSprayCan(canPos, screen, deltaTime);
		}
		CollisionCollectablesPaddle();
	}

	//Collision functions
	CollisionBallPaddle();
	if (ball.GetPos2().y >= ScreenHeight)
	{
		// If the ball touches the ground the player will lose a life and the position of the ball and the paddle will reset
		livesCounter--;
		Restart();

		// If the player loses all lives the level will reset
		if(livesCounter==0)
		{
			livesCounter = 3;
			initialized = false;
		}
	}
	// If the big paddle power-up is active the timer value decreases and when it reaches 0 it will stop the power-up
	if (paddle.GetPowerUpStatus())
	{
		paddlePowerUpTimer--;
		if (!paddlePowerUpTimer)
		{
			paddle.SetPowerUpStatus(false);
		}
	}
}

// LOAD THE FIRST LEVEL
void Level::LoadLevel1(Tmpl8::Surface* screen, LevelType& level)
{
	// Initialize the level
	if (!initialized) 
	{
		Restart();
		livesCounter = 3;
		int j = 0;

		// Render the bricks
		for (auto& brick : bricks) 
		{
			pos.x = 40.0f + colloum * 95;
			pos.y = 70.0f + rows * 46;

			delete brick;
			brick = new Brick(wokia_sprite,brick1_sprite,brick2_sprite,pos, map.level1[j]);
			colloum++;
			if (colloum > 5) {
				rows++;
				colloum = 0;
			}
			brick->DrawBrick(screen);
			j++;
		}
		rows = 0;
		initialized = true;
	}
	// If the level has already been initialized it will just draw the bricks and check the collisions
	else
	{
		bool checkBrickState = true; // This variable checks if there is no brick left to break
		bool collided = false;
		for (auto i : bricks)
		{
			if (checkBrickState)
			{
				if (i->GetState() == State::HIT1 || i->GetState() == State::HIT2)
				{
					checkBrickState = false;
				}
			}
			i->DrawBrick(screen);
			if (!collided)
			{
				collided = checkCollision(i, screen);
			}
		}
		// If all the brick states are nothing or wokia it will automatically go to level 2
		if (checkBrickState)
		{
			screen->Clear(0);
			Restart();
			level = LevelType::SECOND;
			initialized = false;
		}
	}
}

// LOAD THE SECOND LEVEL
void Level::LoadLevel2(Tmpl8::Surface* screen, LevelType& level)
{
	// Initialize the level
	if (!initialized) 
	{
		Restart();
		livesCounter = 3;
		int j = 0;

		// Render the bricks
		for (auto& brick : bricks) 
		{
			pos.x = 40.0f + colloum * 95;
			pos.y = 70.0f + rows * 46;

			delete brick;
			brick = new Brick(wokia_sprite, brick1_sprite, brick2_sprite, pos, map.level2[j]);
			colloum++;
			if (colloum > 5)
			{
				rows++;
				colloum = 0;
			}
			brick->DrawBrick(screen);
			j++;
		}
		rows = 0;
		initialized = true;
	}
	// If the level has already been initialized it will just draw the bricks and check the collisions
	else
	{
		bool checkBrickState = true; // This variable checks if there is no brick left to break
		bool collided = false;
		for (auto i : bricks)
		{
			if (checkBrickState)
			{
				if (i->GetState() == State::HIT1 || i->GetState() == State::HIT2)
				{
					checkBrickState = false;
				}
			}
			i->DrawBrick(screen);
			if (!collided)
			{
				collided = checkCollision(i, screen);
			}
		}
		// If all the brick states are nothing or wokia it will automatically go to level 3
		if (checkBrickState)
		{
			screen->Clear(0);
			Restart();
			level = LevelType::THIRD;
			initialized = false;
		}
	}
}

// LOAD THE THIRD LEVEL
void Level::LoadLevel3(Tmpl8::Surface* screen, bool& inMenu)
{
	// Initialize the level
	if (!initialized) 
	{
		Restart();
		livesCounter = 3;
		int j = 0;

		// Render the bricks
		for (auto& brick : bricks) 
		{
			pos.x = 40.0f + colloum * 95;
			pos.y = 70.0f + rows * 46;

			delete brick;
			brick = new Brick(wokia_sprite, brick1_sprite, brick2_sprite, pos, map.level3[j]);
			colloum++;
			if (colloum > 5)
			{
				rows++;
				colloum = 0;
			}
			brick->DrawBrick(screen);
			j++;
		}
		rows = 0;
		initialized = true;
	}
	// If the level has already been initialized it will just draw the bricks and check the collisions
	else
	{
		bool checkBrickState = true; // This variable checks if there is no brick left to break
		bool collided = false;
		for (auto i : bricks)
		{
			if (checkBrickState)
			{
				if (i->GetState() == State::HIT1 || i->GetState() == State::HIT2)
				{
					checkBrickState = false;
				}
			}
			i->DrawBrick(screen);
			if (!collided)
			{
				collided = checkCollision(i, screen);
			}
		}
		// If all the brick states are nothing or wokia it will automatically go back to the menu
		if (checkBrickState)
		{
			screen->Clear(0);
			Restart();
			inMenu = true;
			initialized = false;
		}
	}
}

// DRAW ON THE SCREEN HOW MANY LIVES ARE LEFT
void Level::DrawLives(Tmpl8::Surface* screen)
{
	switch (livesCounter)
	{
	case 3:
		lives.Draw(screen, ScreenWidth- lives.GetWidth()-4, 10);
		lives.Draw(screen, ScreenWidth - 2 * lives.GetWidth() - 8, 10);
		lives.Draw(screen, ScreenWidth - 3 * lives.GetWidth() - 12, 10);
		break;
	case 2:
		lives.Draw(screen, ScreenWidth - lives.GetWidth() - 4, 10);
		lives.Draw(screen, ScreenWidth - 2 * lives.GetWidth() - 8, 10);
		break;
	case 1:
		lives.Draw(screen, ScreenWidth - lives.GetWidth() - 4, 10);
		break;
	default: break;
	}
}