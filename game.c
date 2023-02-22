#include "game.h"

void Play() {
	SDL_Texture *StartBgTexture = SDL_CreateTextureFromSurface(Renderer, StartBgSurface);
	SDL_RenderCopy(Renderer, StartBgTexture, NULL, NULL);
	SDL_RenderPresent(Renderer);
	SDL_DestroyTexture(StartBgTexture);
	while (SDL_WaitEvent(&MainEvent)) {
		switch (MainEvent.type) {
			case SDL_QUIT:
				FreeAndQuit();
				return;
			default:
				break;
		}
	}	
}

void Load() {
	Window = SDL_CreateWindow("07Yusuf11 JigSaw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 972, 1296, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	StartBgSurface = IMG_Load("image/StartBg.png");
}

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
