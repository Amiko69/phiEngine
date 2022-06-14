#include<stdafx.h>
#include"PhiEngine.h"
#include<iostream>
#include<Game.h>
#include<GameObj.h>


#undef main
using namespace phiE;

const Uint8 fps = 60;
const Uint16 Fdelay = 1000 / fps;

const short WID = 1000;
const short HEI = WID;




int main(int argc, char* argv[]) {	
	
	WindowSettings settings = WindowSettings().position(0, 0).size(1000, 300).title("bruh").isFullscreen(0).center(1).VSync(1);
	Game game = Game(settings, new EventHandler);
	TextureManager::renderer = game.getRenderer();

	TextureManager::addTexture("Very Gud.jpg", "player");
	SDL_Texture* tex = TextureManager::textures["player"];

	
	while (!game.gameClosed)
	{
		SDL_RenderClear(game.getRenderer());
		game.update();
		
		SDL_RenderCopy(game.getRenderer(), tex, NULL, NULL);
		SDL_RenderPresent(game.getRenderer());
	}
	return 0;
}



