#pragma once
#include <SFML/Graphics.hpp>
#include "GameCharacter.h"
#include <vector>



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



};
