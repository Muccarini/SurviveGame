#pragma once
#include "Character.h"
#include <ctime>

enum Pos {TOP_LEFT , TOP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

enum BoostType {HP, MS};

class Boost :
	public Entity
{
public:
	Boost(sf::Vector2f spawn_pos, std::vector<const sf::Texture &> textures;);
	virtual ~Boost();

	bool checkCollide(sf::FloatRect character);
	void boostSubject(std::shared_ptr<Character> character);

	BoostType getType();
	Textures::ID getId();

private:
	void initHp();
	void initMs();

	void initPos();
	void initSpriteHp();
	void initHitBoxHp();

	void initSpriteMs();
	void initHitBoxMs();

	BoostType id;
	Pos position;

	sf::Vector2f pos;
};

