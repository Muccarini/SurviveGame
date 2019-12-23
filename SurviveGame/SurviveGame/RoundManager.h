#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Subject.h"

class RoundManager : public Subject
{
public:
	RoundManager();
	virtual ~RoundManager();

	virtual void subscribe(Observer* obs);
	virtual void unsubscribe(Observer* obs);

	virtual void notify();

	void increaseRound();
	void increaseKills();
	void reset();
	void startCountdown(sf::Time deltaTime);

	bool isBossRound();

	sf::Time getCountdown();
	bool isLoading();
	int getCounterRound();
	void setBossRound(bool boolean);

	void setKills(int kills);
	int getKills();
	int getKillsPerRound();
	int getRoundPerBoss();


private:
	sf::Time countdown;
	bool loading;

	int kill_counter;
	const int kills_per_round = 10;
	const int round_per_boss = 4;

	int counter_round;
	bool boss;

	std::list<Observer *> observers;
};

