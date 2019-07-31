#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "GameCharacter.h"



class Game
{
public:
	Game();
	
	void run();

private:
	void processEvents(); //GESTISCE TUTTI GLI EVENTI DELL'UTENTE
	void handlePlayerInput(sf::Keyboard::Key key);

	void update(sf::Time deltaTime); // AGGIORNA LO STATO DELL'INTERO GIOCO
	void render();// GESTISCE TUTTI I RENDERING DEL GIOCO



	sf::RenderWindow _window; //CON TextureHolder POSSIAMO GESTIRE PIU TEXTURE ALLA VOLTA (LOAD AND GET)
	GameCharacter _player;   // SPRITE NE GESTICE LA POSIZIONE E L'ORIENTAMENTO

};
