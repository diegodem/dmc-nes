// Code by Diego de Miguel (https://github.com/diegodem) - March 2021

#include "Player.h"
#include <SDL.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>




Player::Player()
{
	maxHealth = 128;
	health = maxHealth;
	speed = 2;
	currentFrame = 0;
	rect = { 128, 160, 16, 32 };
	attackRect = { rect.x, rect.y, 32, 32 };
	swordRect = { rect.x + 24, rect.y + 8, 10, 8 };
	frameTimer.start();
	swordDamage = 64;
	state = STANDING_RIGHT;
	immuneState = 0;
	immunityTimer.start();
	canShoot = true;
	ammo = 50;
}

void Player::update()
{
	if (state == ATTACKING_RIGHT && frameTimer.getTime() > 0.2f)
	{
		state = AFTER_ATTACK_RIGHT;
		currentFrame = 0;
	}
	else if (state == ATTACKING_LEFT && frameTimer.getTime() > 0.2f)
	{
		state = AFTER_ATTACK_LEFT;
		currentFrame = 2;
	}
	if (immuneState > 0)
	{
		(immuneState == 1) ? immuneState = 2 : immuneState = 1;
		if (immunityTimer.getTime() >= 1)
		{
			immuneState = 0;
		}
	}
}

void Player::moveLeft(float deltaTime)
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT || state == STANDING_LEFT || state == MOVING_LEFT || state == AFTER_ATTACK_LEFT || state == AFTER_ATTACK_RIGHT)
	{
		if (rect.x > 0)
		{
			rect.x -= (int)(59.f * deltaTime) * speed;
			attackRect.x = rect.x - 18;
			swordRect.x = attackRect.x;
			if (state != MOVING_LEFT)
			{
				state = MOVING_LEFT;
				frameTimer.start();
				currentFrame = 3;
			}
			else if (frameTimer.getTime() > 0.2f)
			{
				frameTimer.start();
				(currentFrame == 2) ? currentFrame = 3 : currentFrame = 2;
			}
		}
		else
		{
			state = STANDING_LEFT;
			currentFrame = 2;
		}
	}
	
	

}

void Player::moveRight(float deltaTime)
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT || state == STANDING_LEFT || state == MOVING_LEFT || state == AFTER_ATTACK_LEFT || state == AFTER_ATTACK_RIGHT)
	{
		if (rect.x < 240)
		{
			rect.x += (int)(59.f * deltaTime) * speed;
			attackRect.x = rect.x;
			swordRect.x = rect.x + 24;
			if (state != MOVING_RIGHT)
			{
				state = MOVING_RIGHT;
				frameTimer.start();
				currentFrame = 1;
			}
			else if (frameTimer.getTime() > 0.2f)
			{
				frameTimer.start();
				(currentFrame == 0) ? currentFrame = 1 : currentFrame = 0;
			}
		}
		else
		{
			state = STANDING_RIGHT;
			currentFrame = 0;
		}
	}
}

int Player::attackSword()
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT)
	{
		state = ATTACKING_RIGHT;
		frameTimer.start();
		currentFrame = 4;
		return 1;
	}
	else if (state == STANDING_LEFT || state == MOVING_LEFT)
	{
		state = ATTACKING_LEFT;
		frameTimer.start();
		currentFrame = 5;
		return 2;
	}
	return 0;
}

void Player::fire()
{
	if (state == STANDING_RIGHT || state == MOVING_RIGHT)
	{
		state = ATTACKING_RIGHT;
		frameTimer.start();
		currentFrame = 0;
		if (canShoot)
		{
			ammo--;
		}
	}
	else if (state == STANDING_LEFT || state == MOVING_LEFT)
	{
		state = ATTACKING_LEFT;
		frameTimer.start();
		currentFrame = 2;
		if (canShoot)
		{
			ammo--;
		}
	}
	if (ammo == 0)
	{
		canShoot = false;
	}
}

void Player::noButtonPressed()
{
	if (state == MOVING_RIGHT)
	{
		currentFrame = 0;
	}
	else if (state == MOVING_LEFT)
	{
		currentFrame = 2;
	}
	else if (state == AFTER_ATTACK_RIGHT)
	{
		state = STANDING_RIGHT;
		
	}
	else if (state == AFTER_ATTACK_LEFT)
	{
		state = STANDING_LEFT;
		
	}
}

SDL_Rect* Player::getRect()
{
	return &rect;
}

SDL_Rect* Player::getAttackRect()
{
	return &attackRect;
}

SDL_Rect* Player::getSwordRect()
{
	return &swordRect;
}

int Player::getCurrentFrame()
{
	return currentFrame;
}

State Player::getState()
{
	return state;
}

int Player::getSwordDamage()
{
	return swordDamage;
}

void Player::takeDamage(int damage)
{
	if (immuneState == 0)
	{
		health -= damage;
		immuneState = 1;
		immunityTimer.start();
	}
	
}

int Player::getHealth()
{
	return health;
}

int Player::getMaxHealth()
{
	return maxHealth;
}


int Player::getImmunityState()
{
	return immuneState;
}

void Player::heal()
{
	sideEffect();
	health = maxHealth;
}

void Player::sideEffect()
{
	switch (rand() % 5)
	{
	case 0:
		maxHealth = std::max(32, maxHealth - 32);
		break;
	case 1:
		if (speed == 2)
		{
			speed = 1;
		}
		else
		{
			swordDamage = std::max(16, swordDamage - 16);
		}
		break;
	case 2:
		swordDamage = std::max(16, swordDamage - 16);
		break;
	case 3:
		if (canShoot)
		{
			canShoot = false;
		}
		else
		{
			maxHealth = std::max(32, maxHealth - 32);
		}
		
		break;
	default:
		break;
	}
}

bool Player::getCanShoot()
{
	return canShoot;
}

int Player::getAmmo()
{
	return ammo;
}