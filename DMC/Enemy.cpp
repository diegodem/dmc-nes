#include "Enemy.h"


SDL_Rect* Enemy::getRect()
{
	return &rect;
}

void Enemy::initializeRect(int x, int y)
{
	rect = { x, y, 16, 32 };
}


void Enemy::startFrameTimer()
{
	frameTimer.start();
}

float Enemy::getFrameTimer()
{
	return frameTimer.getTime();
}

int Enemy::getCurrentFrame()
{
	return currentFrame;
}

void Enemy::moveRect(int x)
{
	rect.x -= x;
}
void Enemy::setFrames(int f1, int f2)
{
	frames[0] = f1;
	frames[1] = f2;
	currentFrame = frames[0];
}

void Enemy::update(float deltaTime)
{

	moveRect((int)(60.f * deltaTime) * speed);
	if (getFrameTimer() > 0.2)
	{
		//(getCurrentFrame() == 0) ? setCurrentFrame(1) : setCurrentFrame(0);
		(currentFrame == frames[0]) ? currentFrame = frames[1] : currentFrame = frames[0];

		startFrameTimer();
	}

}

void Enemy::takeDamage(int damage)
{
	health -= damage;
}

int Enemy::getHealth()
{
	return health;
}
