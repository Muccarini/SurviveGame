#include "Pet.h"



Pet::Pet(const std::shared_ptr<EntityData> entitydata)
{
	this->textures = entitydata->textures;
	this->texture = textures->get(Textures::Pet);
	this->texture_bullet = textures->get(Textures::Proiettile);

	initVar();
	initSprite(entitydata->boss->getPosition());
	initHitbox();
}

Pet::Pet()
{
}


Pet::~Pet()
{
}

void Pet::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->player, entitydata->deltaTime);
	updateRotate(entitydata->mouse_pos_view);
	updateBullets(entitydata);
	updateHud();
	updateCollision(entitydata);
}

void Pet::takeDamage()
{
	this->hp--;
}

void Pet::renderBullets(const std::shared_ptr<sf::RenderWindow> window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render(window);
	}
}

void Pet::updateMove(std::shared_ptr<Character> target, sf::Time deltaTime)
{
	sf::Vector2f dir = target->getPosition() - this->getPosition();

	this->sprite.move((dir.x * this->mov_speed * deltaTime.asSeconds()), (dir.y * this->mov_speed * deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Pet::updateRotate(sf::Vector2f mouse_pos)
{
	float dX = mouse_pos.x - getPosition().x;
	float dY = mouse_pos.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 270.f);
}

void Pet::updateBullets(std::shared_ptr<EntityData> entitydata)
{
	if (entitydata->player->isShooting() && entitydata->player->getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Pet, texture_bullet));
		bullets.emplace_back(bullet);
		bullet->setDir(this->getPosition(), entitydata->mouse_pos_view);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update(entitydata);
		if (bullets[i]->isCollide())
			bullets.erase(bullets.begin() + i);
	}
}

void Pet::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Pet::updateCollision(std::shared_ptr<EntityData> entitydata)
{ //PLAYER
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	
	collision->resetOutMtv();
}

void Pet::initVar()
{
	mov_speed_default = 1.f;
	mov_speed = mov_speed_default;

	hp_max = 25;
	hp = hp_max;

	range = 50;
}

void Pet::initSprite(sf::Vector2f spawn_pos)
{
	sprite.setTexture(texture);     //TEXTURE
	sprite.setScale(0.1, 0.1);      //SCALE
	sprite.setPosition(spawn_pos);  //POS
	sprite.setOrigin(222.f, 188.f);      //ORIGIN
}

void Pet::initHitbox()
{
	hit_box.setSize(sf::Vector2f(445, 377));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());           //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(222.f, 188.f);                       //ORIGIN
}
