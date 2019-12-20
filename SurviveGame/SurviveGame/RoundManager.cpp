#include "RoundManager.h"



RoundManager::RoundManager()
{
	countdown = sf::seconds(6.f);
	loading = true;
	boss = false;
	counter_round = 1;
}


RoundManager::~RoundManager()
{
}

void RoundManager::subscribe(Observer* obs)
{
	this->observers.push_back(obs);
}

void RoundManager::unsubscribe(Observer* obs)
{
	this->observers.remove(obs);
}

void RoundManager::notify()
{
	for (auto itr = std::begin(observers); itr != std::end(observers); itr++)
	{//PULL O PUSH DECIDERE SE SALVARE I DATI QUI SU ROUND MANAGER O SU ACHIEVEMENT
		(*itr)->update();
	}
}

void RoundManager::increase()
{
	this->counter_round++;
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

int RoundManager::getCounterRound()
{
	return
		this->counter_round;
}

void RoundManager::setBossRound(bool boolean)
{
	this->boss = boolean;
}

int RoundManager::getKillsPerRound()
{
	return
		this->kills_per_round;
}

int RoundManager::getRoundPerBoss()
{
	return
		this->round_per_boss;
}
