#include <iostream>
#include "SDL.h"


int main(){
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	std::cout << "SDL initialized successfully!" << std::endl;
	SDL_Quit();
	return 0;
}
