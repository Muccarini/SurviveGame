#pragma once
#include "Character.h"
#include "TextureHolder.h"
#include "boost.h"
#include "StrategyFight.h"

class StrategyFight;

class PlayerT : public Character
{
public:
	PlayerT(Textures::ID id, std::shared_ptr<StrategyFight> stf);

	PlayerT();
	virtual ~PlayerT();

	void updateMove(const sf::Time& delta_time);
	void updateRotate(const sf::Vector2f target);
	bool updateReload(const sf::Time& delta_time);
	void updateMovSpeed(const sf::Time& delta_time);
	void updateHud();

	void boost(BoostType::Type b_type);

	bool shooting(const sf::Time& delta_time);
	void setStrategyFight(std::shared_ptr<StrategyFight> stf);

	Textures::ID getId();
	std::shared_ptr<StrategyFight> getStf();

	void setTexturesSprite(const sf::Texture& texture);

private:

	void initVar();
	void initSprite();
	void initHitBox();
	void initType();

	Textures::ID id;
	CharacterType::Type type;

	std::shared_ptr<StrategyFight> stf;
	const float ms_cd = 3.f;
	float ms_clock;
};

