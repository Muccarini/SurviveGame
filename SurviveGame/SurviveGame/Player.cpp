#include "Player.h"


Player::Player()
{
	_movementSpeed = 190;
	//caratteristiche dello sprite e del suo FloatRect
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprShape.setSize(sf::Vector2f(_sprite.getGlobalBounds().width, _sprite.getGlobalBounds().height));
	_sprShape.setFillColor(sf::Color::Transparent);
	_sprShape.setOutlineColor(sf::Color::Magenta);
	_sprShape.setOutlineThickness(3.f);


	_sprite.setPosition(1000.f, 400.f);
	_sprShape.setPosition(_sprite.getPosition());
	_sprite.setScale(0.2, 0.2);
	_sprShape.setScale(_sprite.getScale());
	       // IL PUNTO DI ROTAZIONE NON E' CENTRATO //
		   // non so se e' 5, 5
	_sprite.setOrigin(100.5,100.5);
	_sprShape.setOrigin(_sprite.getOrigin());
	//quadrato che penso utilizzerò per le collisioni 
	_colBox = _sprite.getGlobalBounds();
	
	
	//!!!RICORDARSI CHE PER OGNI SET DI _sprite DI DEVE FARE IMMEDIATAMENTE DOPO IL SET DEL _sprShape!!!\\

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
	_oldPos = this->_sprite.getPosition();
	move(deltaTime);
	sf::Vector2f moveVector;
	moveVector.x = (_sprite.getPosition().x - _oldPos.x);
	moveVector.y = (_sprite.getPosition().y - _oldPos.y);


	float dX = /*sf::Mouse::getPosition().x*/ mousePosView.x - this->_sprite.getPosition().x; //mousePosView.x;
	float dY = /*sf::Mouse::getPosition().y*/ mousePosView.y - this->_sprite.getPosition().y; //mousePosView.y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->_sprite.setRotation(deg + 360.f);
	this->_sprShape.setPosition(_sprite.getPosition() + moveVector);
	this->_sprShape.setRotation(deg + 360.f);
	this->_colBox = _sprShape.getGlobalBounds();
		
		
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
