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
	Boost(const sf::Vector2f spawn_pos, BoostType::Type type, const sf::Texture & texture);
	Boost() {};
	virtual ~Boost();

	bool checkCollide(sf::FloatRect character);

	BoostType::Type getType();

private:
	void initHp(const sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initMs(const sf::Vector2f spawn_pos, const sf::Texture & texture);

	void initSpriteHp(const sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxHp();

	void initSpriteMs(const sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxMs();

	BoostType::Type b_type;
};

