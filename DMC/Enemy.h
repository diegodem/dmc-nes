// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

#pragma once
#include <SDL.h>
#include "Timer.h"

class Enemy
{
public:
	void initializeRect(int x, int y);
	void update(float deltaTime);
	SDL_Rect* getRect();
	void setFrames(int f1, int f2);
	void startFrameTimer();
	float getFrameTimer();
	int getCurrentFrame();
	void moveRect(int x);
	void takeDamage(int damage);
	int getHealth();
	void pushBack(int pixels, int direction);
	int getScore();
protected:
	int speed = 1;
	int health = 64;
	int score = 10;
private:
	SDL_Rect rect;
	Timer frameTimer;
	int frames[2];
	int currentFrame;
	int direction;
	
};