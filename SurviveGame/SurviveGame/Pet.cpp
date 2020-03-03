#include "Pet.h"



Pet::Pet(const std::shared_ptr<EntityData> entitydata)
{
	this->entitydata = entitydata;

	initVar();
	initSprite();
	initHitbox();
}

Pet::Pet()
{
}


Pet::~Pet()
{
}

void Pet::update()
{
	updateMove();
	updateRotate();
	updateBullets();
	updateHud();
	updateCollision();
}

void Pet::takeDamage()
{
	this->hp--;
}

void Pet::renderBullets(const std::shared_ptr<sf::RenderWindow> window)
{
	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->render(window);
	}
}

void Pet::updateMove()
{
	sf::Vector2f dir = entitydata->player->getPosition() - this->getPosition();

	this->sprite.move((dir.x * this->mov_speed * entitydata->deltaTime.asSeconds()), (dir.y * this->mov_speed * entitydata->deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Pet::updateRotate()
{
	float dX = entitydata->mouse_pos_view.x - getPosition().x;
	float dY = entitydata->mouse_pos_view.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 270.f);
}

void Pet::updateBullets()
{
	if (entitydata->player->isShooting() && entitydata->player->getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Pet, entitydata));
		bullets.emplace_back(bullet);
		bullet->calculateDir();
	}

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->update();
		if (bullets[i]->isCollide())
			bullets.erase(bullets.begin() + i);
	}
}

void Pet::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Pet::updateCollision()
{ //PLAYER
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	
	collision->resetOutMtv();
}

void Pet::initVar()
{
	mov_speed_default = 1;
	mov_speed = mov_speed_default;

	hp_max = 25;
	hp = hp_max;

	range = 50;
}

void Pet::initSprite()
{
	sprite.setTexture(entitydata->textures->get(Textures::Pet));     //TEXTURE
	sprite.setScale(0.1f, 0.1f);      //SCALE
	sprite.setPosition(entitydata->boss->getPosition());  //POS
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
