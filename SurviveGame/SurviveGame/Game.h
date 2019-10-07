#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "TileMap.h"
#include "GameCharacter.h"
#include <vector>
#include "Box2D/Box2D.h"



class Game
{
public:
	explicit Game();
	
	void run();

private:
	void processEvents(); //GESTISCE TUTTI GLI EVENTI DELL'UTENTE

	void update(sf::Time deltaTime); // AGGIORNA LO STATO DELL'INTERO GIOCO
	void render();// GESTISCE TUTTI I RENDERING DEL GIOCO



	sf::RenderWindow window;
	sf::View game_view;
	sf::Vector2f mouse_pos_view;

	std::vector<GameCharacter *> enemies;
	GameCharacter *player;

	sf::RenderWindow _window;
	Player _player;
	Enemy _enemy;


};
