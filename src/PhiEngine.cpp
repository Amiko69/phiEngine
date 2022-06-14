#include<stdafx.h>
#include"PhiEngine.h"
#include<iostream>




namespace phiE {
	
	
	bool Init() {
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			throw "SDL could not initialize! SDL_Error: %s\n", SDL_GetError();
			return false;
		}
		else if (!IMG_Init(IMG_INIT_JPG
			| IMG_INIT_PNG
			| IMG_INIT_TIF
			| IMG_INIT_WEBP)) {
			std::cout << "SDL_image could not initialize! SDL_image Error: "<< IMG_GetError() << "\n";
			return false;
		}
		return true;
	}

	double Map(double value, double fromMin, double fromMax, double toMin, double toMax) {
		return (value - fromMin) * (toMax - toMin) / (fromMax - fromMin) + toMin;
	}
	
	void setPixel(SDL_Surface* surface, int x, int y, Uint32 pixel) {
		int bpp = surface->format->BytesPerPixel;
		/* Here p is the address to the pixel we want to set */
		Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
		
		switch (bpp) {
			case 1:
				*p = pixel;
				break;
			case 2:
				*(Uint16 *)p = pixel;
				break;
			case 3:
				if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				}
				else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;
			case 4:
				*(Uint32 *)p = pixel;
				break;
		}
	}
	void setPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b) {
		Uint32 pixel = SDL_MapRGB(surface->format, r, g, b);
		setPixel(surface, x, y, pixel);
	}
	void setPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
		Uint32 pixel = SDL_MapRGBA(surface->format, r, g, b, a);
		setPixel(surface, x, y, pixel);
	}
	
}