#include "RoundManager.h"



RoundManager::RoundManager()
{
	countdown = sf::seconds(6.f);
	loading = true;
	boss = false;
	counter = 1;
	boss_ratio = 3;
}


RoundManager::~RoundManager()
{
}

void RoundManager::increase()
{
	this->counter++;
}

void RoundManager::reset()
{
	loading = true;
	countdown = sf::seconds(6.f);
}

void RoundManager::startCountdown(sf::Time deltaTime)
{
	countdown -= deltaTime;
	if (countdown <= sf::seconds(1.f))
		loading = false;
}

bool RoundManager::isBossRound()
{
	return 
		this->boss;
}

sf::Time RoundManager::getCountdown()
{
	return this->countdown;
}

bool RoundManager::isLoading()
{
	return this->loading;
}

int RoundManager::getCounter()
{
	return
		this->counter;
}

void RoundManager::setBossRound(bool boolean)
{
	this->boss = boolean;
}
