#include "Pet.h"



Pet::Pet(sf::Texture txt_p, sf::Texture txt_b, sf::Vector2f spawn_pos)
{
	this->texture = txt_p;
	this->texture_bullet = txt_b;

	initVar();
	initSprite(spawn_pos);
	initHitbox();
}


Pet::~Pet()
{
}

void Pet::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->player, entitydata->deltaTime);
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

void Pet::updateBullets(std::shared_ptr<EntityData> entitydata)
{
	if (entitydata->player->isShooting() && entitydata->player->getAmmo())
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Allied, texture_bullet));
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
	if (ent.x != 0 || ent.y != 0)
		entitydata->player->takeDamage();
	//hit_box.setPosition(getPosition());
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
	sprite.setScale(0.01, 0.01);      //SCALE
	sprite.setPosition(spawn_pos);  //POS
	sprite.setOrigin(92, 120);      //ORIGIN
}

void Pet::initHitbox()
{
	hit_box.setSize(sf::Vector2f(80, 80));     //SIZE
	hit_box.setOutlineColor(sf::Color::Red); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	/*hit_box.setScale(sprite.getScale()); */            //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(40, 40);                       //ORIGIN
}
