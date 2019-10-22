#include "Bullet.h"



Bullet::Bullet(sf::Vector2f player_pos) : player_pos(player_pos)
{
	mov_speed = 200;
	//TEXTURE
	//_textures.load(Textures::Proiettile, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));

	hit_box.setSize(sf::Vector2f(100.f, 100.f));

	//COLOR
	hit_box.setOutlineColor(sf::Color::Red);
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	//SCALE
	_sprite.setScale(0.1, 0.1);
	hit_box.setScale(_sprite.getScale());
	//POSITION
	_sprite.setPosition(player_pos);
	hit_box.setPosition(getPosition());
	//ORIGIN
	_sprite.setOrigin(92, 121);
	hit_box.setOrigin(47.5, 50);
}

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::update(sf::Time deltaTime, sf::Vector2f mousePosView, std::vector<sf::FloatRect> collision, std::vector<std::shared_ptr<Enemy>> enemies)
{
	float dX = player_pos.x - mousePosView.x;
	float dY = player_pos.y - mousePosView.y;

	float lenght = sqrt(pow(dX, 2) + pow(dY, 2));

	sf::Vector2f normVect(dX / lenght, dY / lenght);

	this->_sprite.move(normVect * this->mov_speed * deltaTime.asSeconds());
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

	rotate(normVect);
}


void Bullet::rotate(sf::Vector2f vec_dir)
{
	const float PI = 3.14159265f;
	float deg = atan2(vec_dir.y, vec_dir.x) * 180.f / PI;

	this->_sprite.setRotation(deg + 90.f);
}