#include "Player.h"


Player::Player() : view(sf::Vector2f(0.f, 0.f), sf::Vector2f(600.f, 280.f))
{
	mov_speed = 250;
	_textures.load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	_sprite.setTexture(_textures.get(Textures::Personaggio));
	_sprite.setScale(0.4, 0.4);
	_sprite.setPosition(100.f, 100.f);
	       // IL PUNTO DI ROTAZIONE NON E' CENTRATO //
		   // non so se e' 5, 5
	_sprite.setOrigin(_sprite.getPosition().x +5, _sprite.getPosition().y +5);
	view.setCenter(this->getPosition());
	view.setSize(600.f, 280.f);

}

Player::~Player()
{
}

void Player::move(sf::Time deltaTime) // TODO// cambiare mov_speed in movSpeed
	{
		sf::Vector2f vectorMov(0.f, 0.f);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = -mov_speed;
			_sprite.move(vectorMov* deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = -mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.y = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			vectorMov.x = 0.f;
			vectorMov.y = 0.f;
			vectorMov.x = mov_speed;
			_sprite.move(vectorMov * deltaTime.asSeconds());
		}
	}

void Player::rotate()
{
	float dX = sf::Mouse::getPosition().x - this->_sprite.getPosition().x;
	float dY = sf::Mouse::getPosition().y - this->_sprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->_sprite.setRotation(deg + 360.f);
}


void Player::update(sf::Time deltaTime)
{
		move(deltaTime);
		rotate();
		view.setCenter(this->getPosition());

}

sf::Vector2f Player::getPosition()
{
	return
		this->_sprite.getPosition();
}


//_window.clear(); //SERVE PER PULIRE IL FRAME SOLITAMENTE FA UN SCHERMATA NERA
//
//_window.draw(_map._tileMap);
//
//
////update della posizione del mouse
//mousePosScreen = sf::Mouse::getPosition();
//_window.setView(_map._view);
//(&_map)->_view.setCenter(_player.getPosition());
//mousePosWindow = sf::Mouse::getPosition(_window);
//
//mousePosView = _window.mapPixelToCoords(mousePosWindow);
//if (mousePosView.x >= 0.f)
//mousePosGrid.x = mousePosView.x / gridSizeU;
//if (mousePosView.y >= 0.f)
//mousePosGrid.y = mousePosView.y / gridSizeU;
