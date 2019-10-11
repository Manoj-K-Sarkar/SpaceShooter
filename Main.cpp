#include <SFML\Audio.hpp>

#include "Game.h"

int main() {
	//Init Game engine
	Game game;
	sf::Music music;
	if (!music.openFromFile("Music/audio.ogg"))
		throw "Could not opening ogg file";
	music.setVolume(50);
	music.play();
	//Game Loop
	while (game.play()) {
		//Update
		game.update();
		
		//Render
		game.render();
	}

	//End Of Application
	return 0;
}