#pragma once
#include <SFML/Graphics.hpp>

class RoundManager
{
public:
	RoundManager();
	~RoundManager();

	void increase();
	void reset();
	void startCountdown(sf::Time deltaTime);

	bool isBossRound();

	sf::Time getCountdown();
	bool isLoading();
	int getCounter();
	void setBossRound(bool boolean);


private:
	sf::Time countdown;
	bool loading;
	int counter;

	int boss_ratio;
	bool boss;
};

