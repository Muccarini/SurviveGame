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
	void increaseBoss();

	void reset();
	void startCountdown(sf::Time deltaTime);

	bool isBossRound();

	sf::Time getCountdown();
	bool isLoading();
	int getCounterRound();
	int getCounterBoss();
	void setBossRound(bool boolean);

	void setKills(int kills);

	int getKills();
	int getTotalKills();
	int getKillsPerRound();
	int getRoundPerBoss();


private:
	sf::Time countdown;
	bool loading;

	int kill_counter;
	int total_kills;
	int boss_counter;

	const int kills_per_round = 1;
	const int round_per_boss = 2;

	int counter_round;
	bool boss;

	std::list<Observer *> observers;
};

