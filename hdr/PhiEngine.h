#include <SDL2/SDL.h>
#include <functional>


#define winSet phiE::WindowSettings()

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define Rmask 0xff000000
#define Gmask 0x00ff0000
#define Bmask 0x0000ff00
#define Amask 0x000000ff
#else
#define Rmask 0x000000ff
#define Gmask 0x0000ff00
#define Bmask 0x00ff0000
#define Amask 0xff000000
#endif


namespace phiE {
	
	double Map(double x, double in_min, double in_max, double out_min, double out_max);
	
	bool Init();
	void setPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
	void setPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void setPixel(SDL_Surface* surface, int x, int y, Uint8 r, Uint8 g, Uint8 b);
	
	
	
}