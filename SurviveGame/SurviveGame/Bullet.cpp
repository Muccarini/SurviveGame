#include "Bullet.h"



Bullet::Bullet()
{
	mov_speed = 500;
	//TEXTURE
	_textures.load(Textures::Proiettile, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Proiettile));

	hit_box.setSize(sf::Vector2f(100.f, 100.f));

	//COLOR
	hit_box.setOutlineColor(sf::Color::Red);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	//SCALE
	_sprite.setScale(0.1, 0.1);
	hit_box.setScale(_sprite.getScale());
	//POSITION

	//ORIGIN
	_sprite.setOrigin(92, 121);
	hit_box.setOrigin(47.5, 50);
}


Bullet::~Bullet()
{
}

void Bullet::update(sf::Time deltaTime, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies)
{
	this->_sprite.move(dir * this->mov_speed * deltaTime.asSeconds());
	hit_box.setPosition(getPosition());

	//COLLISON SUI MURI

	for (int i = 0; i != collision.size(); i++)
	{
		if (sat_test(hit_box.getGlobalBounds(), collision[i], &out_mtv))
		{
		
		}
	}
	//COLLISION SUGLI ALTRI ZOMBIE

	for (int i = 0; i != enemies.size(); i++)
	{
		if (enemies[i]->hit_box.getGlobalBounds() != hit_box.getGlobalBounds())
			if (sat_test(hit_box.getGlobalBounds(), enemies[i]->hit_box.getGlobalBounds(), &out_mtv))
			{
				
			}
	}

	rotate(dir);
}

bool Bullet::init(Player *owner, sf::Vector2f mousePosView)
{
	_sprite.setPosition(owner->getPosition());
	float dX = mousePosView.x - owner->getPosition().x;
	float dY = mousePosView.y - owner->getPosition().y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	dir = normVect;

	return true;
}


void Bullet::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->_sprite.setRotation(deg + 90.f);
}