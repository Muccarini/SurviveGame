#include "Enemy.h"


Enemy::Enemy(const std::shared_ptr<EntityData> entitydata) : _m(*entitydata->grid)
{
	this->entitydata = entitydata;

	initVar();
	initSprite();
	initHitBox();
}

Enemy::Enemy() : _m(*this->entitydata->grid)
{
}


Enemy::~Enemy()
{
}

void Enemy::updateMove()
{
	float dx = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dy = entitydata->player->getPosition().y - this->sprite.getPosition().y;
	sf::Vector2i mv;

	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));

	sf::Vector2f normVect(dx / lenght, dy / lenght);

	/*this->sprite.move((normVect.x * this->mov_speed * entitydata->deltaTime.asSeconds()), (normVect.y * this->mov_speed * entitydata->deltaTime.asSeconds()));*/
	if (max_distance == 64 && this->target != this->entitydata->player->getPosition())
	{
		if (!move_vect.empty())
			move_vect.clear();
		this->_m.move(this->entitydata->deltaTime, this->sprite, this->entitydata->player->getPosition(), move_vect);
		this->target.x = this->entitydata->player->getPosition().x;
		this->target.y = this->entitydata->player->getPosition().y;
	}

	if (!move_vect.empty())
	{
		mv = sf::Vector2i(move_vect.front());
		spostamento = static_cast <sf::Vector2f> (mv) * static_cast<float>(this->mov_speed) * this->entitydata->deltaTime.asSeconds();
		distance = sqrt(pow(spostamento.x, 2) + pow(spostamento.y, 2));
		max_distance -= distance;
		if (max_distance <= 0)
		{
			max_distance += distance;
			if (mv.x == 1)
			{
				spostamento.x = max_distance;
				spostamento.y = 0;
			}
			else if (mv.y == 1)
			{
				spostamento.y = max_distance;
				spostamento.x = 0;
			}
			else if (mv.x == -1)
			{
				spostamento.x = -max_distance;
				spostamento.y = 0;
			}
			else if (mv.y == -1)
			{
				spostamento.y = -max_distance;
				spostamento.x = 0;
			}
			this->sprite.move(spostamento);
			max_distance = 64;
		}
		else
		{
			this->sprite.move(spostamento);
		}
		if (max_distance == 64)
		{
			move_vect.pop_front();
		}
	}

	hit_box.setPosition(getPosition());
	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::updateRotate()
{
	float dX = entitydata->player->getPosition().x - this->sprite.getPosition().x;
	float dY = entitydata->player->getPosition().y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 90.f);
}

void Enemy::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Enemy::updateCollision()
{
	sf::Vector2f ent(0, 0);
	sf::Vector2f dir(0, 0);

	//PLAYER
	ent = this->collision->CollideWithEntity(entitydata->player->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
	sprite.move(-ent);
	if (ent.x != 0 || ent.y != 0)
		entitydata->player->takeDamage();
	collision->resetOutMtv();

	//PET
	if (entitydata->pet)
	{
		ent = this->collision->CollideWithEntity(entitydata->pet->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		if (ent.x != 0 || ent.y != 0)
			entitydata->pet->takeDamage();
		collision->resetOutMtv();
	}

	//OTHER ENEMY
	/*std::vector<std::shared_ptr<Character>> enemies;
	enemies = *entitydata->enemies;

	for(unsigned int i = 0; i < enemies.size(); i++)
	{
		ent = this->collision->CollideWithEntity(enemies[i]->getHitBox().getGlobalBounds(), this->getHitBox().getGlobalBounds());
		sprite.move(-ent);
		collision->resetOutMtv();
	}
*/
	//WALLS
	dir = this->collision->CollideWithWalls(this->getHitBox().getGlobalBounds(), entitydata->map->findWalls(static_cast<int>(sprite.getPosition().x), static_cast<int>(sprite.getPosition().y)));
 	sprite.move(dir);
	hit_box.setPosition(getPosition());
	collision->resetOutMtv();

	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::update()
{
	updateCollision();
	if (this->entitydata->grid->getGrid()[gridpos.y][gridpos.x].walkable)
		updateMove();
	updateRotate();
	updateHud();
}

void Enemy::renderBullets(std::shared_ptr<sf::RenderWindow> target)
{
		/*for (int i = 0; i < bullets.size(); i++)
			bullets[i]->render(target);*/
}


void Enemy::initVar()
{
	mov_speed = 100;
	hp = 10;
	max_distance = 64;
}

void Enemy::initSprite()
{
	sprite.setTexture(entitydata->textures->get(Textures::Enemy));
	sprite.setScale(0.9f, 0.9f);
	int k = /*7;*/rand() % 17 + 1;//max 1920
	int j = /*6;*/rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!this->entitydata->grid->getGrid()[j][k].walkable)
	{
		j++;
		k++;
	}
	sprite.setPosition(32 + k * 64, 32 + j * 64);
	sprite.setOrigin(+34.f, +34.f);
	sprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
}

void Enemy::initHitBox()
{
	this->hit_box.setSize(sf::Vector2f(60.f, 60.f));
	this->hit_box.setOutlineColor(sf::Color::Blue);
	this->hit_box.setFillColor(sf::Color::Transparent);
	this->hit_box.setScale(sprite.getScale());
	this->hit_box.setPosition(getPosition());
	this->hit_box.setOrigin(30, 30);
	setGridPosition(this->entitydata->map->getGridSize());
}

void Enemy::takeDamage()
{// a seconda del tipo di proiettile da cui viene colpito take dmg
	this->hp--;
}

