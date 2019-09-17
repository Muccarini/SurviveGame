#include "Player.h"


Player::Player()
{
	_movementSpeed = 190;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setScale(0.2, 0.2);
	_sprite.setPosition(100.f, 100.f);
	       // IL PUNTO DI ROTAZIONE NON E' CENTRATO //
		   // non so se e' 5, 5
	_sprite.setOrigin(_sprite.getPosition().x +5, _sprite.getPosition().y +5);
	//quadrato che penso utilizzerò per le collisioni 
	_colBox = _sprite.getGlobalBounds();
	
}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime)
{
	//_sprite.move(dir_x * deltaTime.asSeconds() * _movementSpeed, dir_y * deltaTime.asSeconds() *_movementSpeed);
	this->_m.move(deltaTime, _sprite, _movementSpeed);
}

void Player::update(sf::RenderWindow &target, sf::Time deltaTime, sf::Vector2f mousePosView)
{
		move(deltaTime);
		
		float dX = sf::Mouse::getPosition().x - this->_sprite.getPosition().x; //mousePosView.x;
		float dY = sf::Mouse::getPosition().y - this->_sprite.getPosition().y; //mousePosView.y;

		const float PI = 3.14159265f;
		float deg = atan2(dY, dX) * 180.f / PI;

		this->_sprite.setRotation(deg + 360.f);
		_colBox = _sprite.getGlobalBounds();
		
		notify(target);

}

void Player::notify(sf::RenderWindow &target)
{
	for (auto i = std::begin(_observers); i != std::end(_observers); i++) 
	{
		(*i)->update(target);
	}
}

void Player::subscribe(Observer * _O)
{
	_observers.push_back(_O);
}

void Player::unsubscribe(Observer * _O)
{
	_observers.remove(_O);
}

void Player::setPositon(sf::Vector2f vMove)
{
	this->_sprite.setPosition(_sprite.getPosition().x + vMove.x,
		_sprite.getPosition().y + vMove.y);
}

sf::Vector2f Player::getPosition()
{
	return
		this->_sprite.getPosition();
}
