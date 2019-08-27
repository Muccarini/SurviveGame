#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include <vector>




class Game
{
public:
	explicit Game();
	
	void run();

private:
	void processEvents(); //GESTISCE TUTTI GLI EVENTI DELL'UTENTE
	void handlePlayerInput(sf::Keyboard::Key key);

	void update(sf::Time deltaTime); // AGGIORNA LO STATO DELL'INTERO GIOCO
	void render();// GESTISCE TUTTI I RENDERING DEL GIOCO



	sf::RenderWindow _window;
	Player _player;
	Enemy _enemy;
	Map _map;
	sf::View _view;


	//init game 
	float gridSizeF = 100.f;
	unsigned gridSizeU = static_cast<unsigned>(gridSizeF);


	//init game elemts
	sf::RectangleShape shape;
};
