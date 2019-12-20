#include "Achievement.h"



Achievement::Achievement()
{
	this->round = 0;
	this->kills = 0;
	this->kills_boss = 0;

	bool alive = false;

	//TESTO
	this->font.loadFromFile("Sources/04B_30__");
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);

	//NUMERO
	this->kills_t.setFillColor(sf::Color::White);
	this->kills_t.setCharacterSize(20);
}


Achievement::~Achievement()
{
}

void Achievement::update()
{
	this->round = this->subject->getCounterRound();
	this->kills = this->round * this->subject->getKillsPerRound();
	if (this->round % this->subject->getRoundPerBoss() == 0)
		this->kills_boss ++;
}

void Achievement::attach()
{
	this->subject->subscribe(this);
}

void Achievement::detach()
{
	this->subject->unsubscribe(this);
}

bool Achievement::getAlive()
{
	return
		this->alive;
}

int Achievement::getKills()
{
	return
		this->kills;
}

int Achievement::getKillsBoss()
{
	return
		this->kills_boss;
}

int Achievement::getRound()
{
	return
		this->round;
}

void Achievement::renderRoundBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view)
{//DA SETTARE POS
	this->text.setString("New Achievement KILLS :");
	this->text.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);

	this->kills_t.setString(std::to_string(kills));
	this->kills_t.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);
}

void Achievement::renderKillsBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view)
{//DA SETTARE POS
	this->text.setString("New Achievement KILLS :");
	this->text.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);

	this->kills_t.setString(std::to_string(kills));
	this->kills_t.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);
}

void Achievement::renderBossBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view)
{//DA SETTARE POS
	this->text.setString("New Achievement KILLS :");
	this->text.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);

	this->kills_t.setString(std::to_string(kills));
	this->kills_t.setPosition(view.getCenter().x - 540, view.getCenter().y - 330);
}
