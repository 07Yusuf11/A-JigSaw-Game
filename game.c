#include "game.h"

void Init() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
}

void FreeAndQuit() {
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	TTF_CloseFont(Font);
	SDL_Quit();
}
