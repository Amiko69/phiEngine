#pragma once
#include<stdafx.h>


namespace phiE {
	class Game;
    class EventHandler {
    public:
        EventHandler();
        EventHandler(Game *parentGame);
        ~EventHandler();
		virtual void handleEvents();

        Game* parent;

        SDL_Event event;

		std::map<SDL_Keycode, bool> keyStates;

    };
	
	class TextureManager {
	public:
		static SDL_Renderer* renderer;

		// Loads image at specified path and return the texture
		static inline SDL_Texture* loadTexture(const char* path, SDL_Renderer* rend = renderer) {
			SDL_Surface* loadedSurface = IMG_Load(path);
			if (loadedSurface == NULL) {
				printf("%s", IMG_GetError());
				return NULL;
			}
			SDL_Texture* texture = SDL_CreateTextureFromSurface(rend, loadedSurface);
			SDL_FreeSurface(loadedSurface);
			return texture;
		}
		
		// Adds a texture to the map as name parameter.
		// You can then use the name to access the texture like this: "textures[NAME]".
		static inline void addTexture(const char* path,
			const char* name, SDL_Renderer* rend = renderer) {
			
			SDL_Texture* tex = loadTexture(path);
			textures[name] = tex;	
		}
		
		static std::map<std::string, SDL_Texture*> textures;
		
	};
}

namespace phiE {

	class WindowSettings {
	public:
		WindowSettings();
		~WindowSettings();

		// set size using Eigen Vector2i
		WindowSettings& size(Eigen::Vector2i size);
		// set size using ints
		WindowSettings& size(int width, int height);
		//set fullscreen
		WindowSettings& isFullscreen(bool);
		//set centered
		WindowSettings& center(bool);
		// set position using Eigen Vector2i
		WindowSettings& position(Eigen::Vector2i position);
		// set position using ints
		WindowSettings& position(int x, int y);
		// set resizable
		WindowSettings& resizable(bool);
		WindowSettings& title(std::string title);
		WindowSettings& icon(std::string icon);
		WindowSettings& VSync(bool);
		

	protected:
		
		bool m_VSync;
		Eigen::Vector2i m_size;
		Eigen::Vector2i m_position;

		std::string m_title;
		bool m_fullscreen;
		bool m_centered;
		bool m_resizable;
		
		friend class Game;
	};
	
	class Game
	{
	public:
			friend class WindowSettings;
		
			Game();
			Game(WindowSettings settings, EventHandler *eventHandler);
			~Game();
			
			SDL_Window* getWindow();
			void update();
			
			SDL_Renderer* getRenderer();
			
			//return the SDL_Window*
			SDL_Window* operator()();

			EventHandler* eventHandler;

			bool gameClosed;
			Eigen::Vector2i windowSize;
	protected:
		Eigen::Vector2f windowPosition;
		std::string m_title;	
		
		SDL_Window* window;
		SDL_Renderer* renderer;

	};
}



