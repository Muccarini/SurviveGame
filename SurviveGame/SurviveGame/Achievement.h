#pragma once

#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "RoundManager.h"

class Achievement : public Observer
{
public:

	Achievement() = default;
	Achievement(RoundManager * subject);
	virtual ~Achievement();

	virtual void update();

	virtual void attach();
	virtual void detach();

	int getKills();
	int getKillsBoss();
	int getRound();

	float getClockKills();

	bool isRoundOn();
	bool isKillsOn();
	bool isBossOn();

	void updateBadge(sf::Time deltaTime);

	void renderRoundBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);
	void renderKillsBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);
	void renderBossBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view);

private:

	RoundManager * subject;

	int kills;
	int kills_drawing;

	int kills_boss;
	int kills_boss_drawing;

	int round;
	int round_drawing;

	bool round_on;
	bool kills_on;
	bool boss_on;

	sf::Font font;

	sf::Text kills_t;
	sf::Text kills_boss_t;
	sf::Text round_t;

	sf::Text text;

	sf::Texture frame;

	float clock_kills;
	float clock_round;
	float clock_boss;
};
