#include "Achievement.h"



Achievement::Achievement(RoundManager * subject)
{
	this->subject = subject;
	this->round = 0;
	this->kills = 0;
	this->kills_boss = 0;

	//TESTO
	this->font.loadFromFile("Sources/04B_30__.ttf");
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(30);

	//KILLS
	this->kills_t.setFont(this->font);
	this->kills_t.setFillColor(sf::Color::White);
	this->kills_t.setCharacterSize(60);

	//ROUND
	this->round_t.setFont(this->font);
	this->round_t.setFillColor(sf::Color::White);
	this->round_t.setCharacterSize(60);

	//BOSS
	this->kills_boss_t.setFont(this->font);
	this->kills_boss_t.setFillColor(sf::Color::White);
	this->kills_boss_t.setCharacterSize(60);

	attach();
}


Achievement::~Achievement()
{
	detach();
}

void Achievement::update()
{
	this->round = this->subject->getCounterRound() - 1;
	this->kills = this->subject->getTotalKills();
	if ((this->round + 1) % (this->subject->getRoundPerBoss()+1) == 0)
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
	this->text.setString("New Achievement ROUND :");
	this->text.setPosition(view.getCenter().x - 350, view.getCenter().y - 330);

	this->round_t.setString(std::to_string(round));
	this->round_t.setPosition(view.getCenter().x + 250, view.getCenter().y - 350);

	window->draw(this->text);
	window->draw(this->round_t);
}

void Achievement::renderKillsBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view)
{//DA SETTARE POS
	this->text.setString("New Achievement KILLS :");
	this->text.setPosition(view.getCenter().x - 350, view.getCenter().y - 330);

	this->kills_t.setString(std::to_string(kills));
	this->kills_t.setPosition(view.getCenter().x + 250, view.getCenter().y - 350);

	window->draw(this->text);
	window->draw(this->kills_t);
}

void Achievement::renderBossBadge(std::shared_ptr<sf::RenderWindow> window, sf::View view)
{//DA SETTARE POS
	this->text.setString("New Achievement BOSS :");
	this->text.setPosition(view.getCenter().x - 350, view.getCenter().y - 330);

	this->kills_boss_t.setString(std::to_string(kills_boss));
	this->kills_boss_t.setPosition(view.getCenter().x + 250, view.getCenter().y - 350);

	window->draw(this->text);
	window->draw(this->kills_boss_t);
}
