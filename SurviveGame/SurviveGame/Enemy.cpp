#include "Enemy.h"


Enemy::Enemy(sf::Texture txt_e)
{
	this->texture = txt_e;
	initVar();
	initSprite();
	initHitBox();
}

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::updateMove(sf::Time deltaTime, const std::shared_ptr<Character> target)
{
	float dx = target->getPosition().x - this->sprite.getPosition().x;
	float dy = target->getPosition().y - this->sprite.getPosition().y;

	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));

	sf::Vector2f normVect(dx / lenght, dy / lenght);

	this->sprite.move((normVect.x * this->mov_speed * deltaTime.asSeconds()), (normVect.y * this->mov_speed * deltaTime.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Enemy::updateRotate(const std::shared_ptr<Character> target)
{
	float dX = target->getPosition().x - this->sprite.getPosition().x;
	float dY = target->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Enemy::updateCollision(std::shared_ptr<EntityData> entitydata)
{
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	if (ent.x != 0 || ent.y != 0)
		entitydata->player->takeDamage();
	//hit_box.setPosition(getPosition());
	collision->resetOutMtv();

	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), entitydata->walls);
 	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();
}

void Enemy::update(std::shared_ptr<EntityData> entitydata)
{
	updateMove(entitydata->deltaTime, entitydata->player);
	updateRotate(entitydata->player);
	updateHud();
	updateCollision(entitydata);
}

void Enemy::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
		/*for (int i = 0; i < bullets.size(); i++)
			bullets[i]->render(target);*/
}


void Enemy::initVar()
{
	mov_speed = 150;
	hp = 10;

	allied = false;
}

void Enemy::initSprite()
{
	sprite.setTexture(texture);
	sprite.setScale(0.9f, 0.9f);
	sprite.setPosition(rand() % 400 + 500.f , rand() % 400 + 500.f);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	this->hit_box.setSize(sf::Vector2f(60.f, 60.f));
	this->hit_box.setOutlineColor(sf::Color::Blue);
	this->hit_box.setOutlineThickness(0.5f);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(30, 30);
}

//void Enemy::collisionWalls(std::vector<sf::FloatRect> walls)
//{
//	for (int i = 0; i != walls.size(); i++)
//	{
//		if (sat_test(hit_box.getGlobalBounds(), walls[i], &out_mtv))
//		{
//			sprite.move(out_mtv);
//		}
//	}
//}
//
//void Enemy::collisionEnemies(std::vector<std::shared_ptr<Character>> enemies)
//{
//	for (int i = 0; i != enemies.size(); i++)
//	{
//		if (enemies[i]->getHitBox().getGlobalBounds() != this->hit_box.getGlobalBounds())
//			if (sat_test(hit_box.getGlobalBounds(), enemies[i]->getHitBox().getGlobalBounds(), &out_mtv))
//			{
//				sprite.move(out_mtv);
//			}
//	}
//}

void Enemy::takeDamage()
{// a seconda del tipo di proiettile da cui viene colpito take dmg
	this->hp--;
}

