#include"stdafx.h"
#include "SDL2/SDL.h"
#include <Game.h>

namespace phiE {
	WindowSettings::WindowSettings():m_VSync(1), m_fullscreen(0), m_centered(0) {}
	WindowSettings::~WindowSettings() {}

	Game::Game(){}
	

	Game::Game(WindowSettings settings, EventHandler *eventHandler = nullptr)
	: window(nullptr), renderer(nullptr),
	gameClosed(0)
	 {
		Eigen::Vector2i _size = settings.m_size;
		window = SDL_CreateWindow(settings.m_title.c_str()
			, settings.m_centered ? SDL_WINDOWPOS_CENTERED : settings.m_position.x()
			, settings.m_centered ? SDL_WINDOWPOS_CENTERED : settings.m_position.x(),
			_size.x(), _size.y(), SDL_WINDOW_SHOWN |
			(settings.m_fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN) |
			(settings.m_resizable ? SDL_WINDOW_RESIZABLE : 0)|
				(settings.m_VSync ? SDL_RENDERER_PRESENTVSYNC : 0)
		);		
		
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		this->eventHandler = eventHandler ;
		this->eventHandler->parent = this;
	}

	Game::~Game() {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
	}

	void Game::update() {
		eventHandler->handleEvents();
		SDL_UpdateWindowSurface(window);
		if (eventHandler->keyStates[SDLK_ESCAPE]) {
			gameClosed = 1;
		}
	}
	SDL_Window* Game::getWindow() {
		return window;
	}
	
	SDL_Renderer* Game::getRenderer() {
		return renderer;
	}
	
	SDL_Window* Game::operator()() {
		return window;
	}
	
	//----------------------------
	WindowSettings& WindowSettings::size(Eigen::Vector2i size) {
		m_size = size;
		return *this;
	}
	WindowSettings& WindowSettings::size(int width, int height){
		m_size = Eigen::Vector2i(width, height);
		return *this;
	}
	WindowSettings& WindowSettings::isFullscreen(bool fs) {
		m_fullscreen = fs;
		return *this;
	}
	WindowSettings& WindowSettings::title(std::string title) {
		m_title = title;
		return *this;
	}
	WindowSettings& WindowSettings::center(bool centered) {
		m_centered = centered;
		return *this;
	}
	WindowSettings& WindowSettings::resizable(bool resizable) {
		m_resizable = resizable;
		return *this;
	}
	WindowSettings& WindowSettings::position(Eigen::Vector2i position) {
		m_centered = false;
		m_position = position;
		return *this;
	}
	WindowSettings& WindowSettings::position(int x, int y) {
		m_centered = false;
		m_position = Eigen::Vector2i(x, y);
		return *this;
	}
	WindowSettings& WindowSettings::VSync(bool _) { m_VSync = _; return *this; }

	EventHandler::EventHandler(){
	}

	EventHandler::EventHandler(Game *parent) : parent(parent) {
		
	}
	EventHandler::~EventHandler() {
		
	}


    void EventHandler::handleEvents(){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    parent->gameClosed = 1;
                    break;
                case SDL_KEYDOWN:
					keyStates[event.key.keysym.sym] = true;
                    break;

                default:
                    break;
            }
        }
    }

	SDL_Renderer* TextureManager::renderer = nullptr;
	std::map<std::string, SDL_Texture*> TextureManager::textures;
}    
