#pragma once
#include "Character.h"
#include <ctime>

namespace BoostType
{
	enum Type {HP = 1, MS = 2 };
};


class Boost :
	public Entity
{
public:
	Boost(sf::Vector2f spawn_pos, BoostType::Type type, sf::Texture texture);
	Boost() {};
	virtual ~Boost();

	bool checkCollide(sf::FloatRect character);
	void boostSubject(std::shared_ptr<Character> character);

	BoostType::Type getType();

private:
	void initHp(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initMs(sf::Vector2f spawn_pos, const sf::Texture & texture);

	//void initPos();
	void initSpriteHp(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxHp();

	void initSpriteMs(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxMs();

	BoostType::Type b_type;
	sf::Vector2f pos;
};

