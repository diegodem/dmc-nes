// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

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
	void takeDamage(int damage);
	int getHealth();
	int getMaxHealth();
	int getImmunityState();
	bool getCanShoot();
	void heal();
	void sideEffect();
	int getAmmo();

private:

	SDL_Rect rect;
	SDL_Rect attackRect;
	SDL_Rect swordRect;
	
	State state;

	Timer frameTimer;

	Timer immunityTimer;

	int currentFrame;

	int speed;

	int swordDamage;

	int maxHealth;
	int health;

	int immuneState;

	bool canShoot;

	int ammo;

};