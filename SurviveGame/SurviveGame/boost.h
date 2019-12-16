#pragma once
#include "Character.h"
#include <ctime>

class BoostPos;

enum Type {HP, MS};

enum Pos {TOP_LEFT , TOP_RIGHT, DOWN_LEFT, DOWN_RIGHT};

class Boost :
	public Entity
{
public:
	Boost(const std::shared_ptr<BoostPos> boost_pos, const std::shared_ptr<TextureHolder> textures);
	virtual ~Boost();

private:
	void update(std::shared_ptr<EntityData> entitydata);

	void initHp();
	void initMs();

	void initPos();
	void initSpriteHp();
	void initHitBoxHp();

	void initSpriteMs();
	void initHitBoxMs();

	Type type;
	Pos position;

	sf::Vector2f pos;

	std::shared_ptr<BoostPos> boost_pos;
};

