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
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void update(sf::Time deltaTime, int framePlayer); // AGGIORNA LO STATO DELL'INTERO GIOCO
	void render();// GESTISCE TUTTI I RENDERING DEL GIOCO



	sf::RenderWindow _window;
	TextureHolder _textures;  //CON TextureHolder POSSIAMO GESTIRE PIU TEXTURE ALLA VOLTA (LOAD AND GET)
	GameCharacter _hero;

};
