#pragma once

#include <SDL.h>
#include "State.h"
#include "Timer.h"


class Player
{
public:
	Player();
	void update();
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	int attackSword();
	void fire();
	void noButtonPressed();
	SDL_Rect *getRect();
	SDL_Rect *getAttackRect();
	SDL_Rect* getSwordRect();
	int getCurrentFrame();
	State getState();
	int getSwordDamage();

private:

	SDL_Rect rect;
	SDL_Rect attackRect;
	SDL_Rect swordRect;
	
	State state;

	Timer frameTimer;

	int currentFrame;

	int swordDamage;

};