#include "game.h"

int IfWin() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[i][j] == count) 
				count++;
		}
	}
	if (count == 15) 
		return 1;
	else 
		return 0;
}

void PrintAll() {
		SDL_Texture *PlayUITexture = SDL_CreateTextureFromSurface(Renderer, PlayUISurface);
		SDL_RenderCopy(Renderer, PlayUITexture, NULL, NULL);
		SDL_DestroyTexture(PlayUITexture);
		PrintTime();
		PrintBlocks();
		SDL_RenderPresent(Renderer);
}

void PrintTime() {
	EndTime = time(NULL);
	int DuraTime = (int) difftime(EndTime, StartTime);
	sprintf(timechar, "%02d:%02d:%02d", DuraTime / 3600, (DuraTime / 60) % 60, DuraTime % 60);
	SDL_Surface *WordSurface = TTF_RenderUTF8_Blended(Font, timechar, FontColor);
	SDL_Texture *WordTexture = SDL_CreateTextureFromSurface(Renderer, WordSurface);
	SDL_Rect TimeRect = {210, 210, WordSurface -> w, WordSurface ->h};
	SDL_RenderCopy(Renderer, WordTexture, NULL, &TimeRect);
	SDL_FreeSurface(WordSurface);
	SDL_DestroyTexture(WordTexture);
}

void PrintBlocks() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int index = arr[i][j];
			BlockRect.x = 45 + 205 * j;
			BlockRect.y = 345 + 205 * i;
			SDL_Texture *BlockTexture = NULL;
			BlockTexture = SDL_CreateTextureFromSurface(Renderer, BlockSurface[index]);
			SDL_RenderCopy(Renderer, BlockTexture, NULL, &BlockRect);
			SDL_DestroyTexture(BlockTexture);

		}
	}
}

void RandomSwap() {
    int temp;
    for (int i = 0;  i < 16; i++) {
        int j = rand() % 4;
        int k = rand() % 4;
        temp = arr[j][k];
        arr[j][k] = arr[i/4][i%4];
        arr[i/4][i%4] = temp;
    }
    return;
}

void PlayUI() {
	StartTime = time(NULL);
	while (1) {
		PrintAll();
		while (SDL_PollEvent(&PlayEvent)) {
			switch (PlayEvent.type) {
				case SDL_QUIT:
					FreeAndQuit();
					return;
				case SDL_MOUSEBUTTONUP:
					printf("(%d,%d) in Play UI\n", PlayEvent.button.x, PlayEvent.button.y);
					break;
			}
		}
	}
}

void Play() {
	while (SDL_WaitEvent(&MainEvent)) {
		SDL_Texture *StartBgTexture = SDL_CreateTextureFromSurface(Renderer, StartBgSurface);
		SDL_RenderCopy(Renderer, StartBgTexture, NULL, NULL);
		SDL_RenderPresent(Renderer);
		SDL_DestroyTexture(StartBgTexture);
		switch (MainEvent.type) {
			case SDL_QUIT:
				FreeAndQuit();
				return;
			case SDL_MOUSEBUTTONUP:
				printf("(%d,%d) in Main UI\n", MainEvent.button.x, MainEvent.button.y);
				if (MainEvent.button.x > 220 && MainEvent.button.x < 670 && MainEvent.button.y > 495 && MainEvent.button.y < 700) {
					printf("In the PlayUI\n");
					PlayUI();
				}
				break;
			default:
				break;
		}
	}	
}

void Load() {
	Window = SDL_CreateWindow("07Yusuf11 JigSaw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 1200, SDL_WINDOW_SHOWN);
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	StartBgSurface = IMG_Load("image/StartBg.png");
	PlayUISurface = IMG_Load("image/PlayUI.png");
	Font = TTF_OpenFont("image/FiraCode-Bold.ttf",45);
	for(int i = 0; i < 16; i++) {
		char FileName[20];
		sprintf(FileName, "image/Block_%d.png", i);
		BlockSurface[i] = IMG_Load(FileName);
	}
	BlockRect.w = BlockSurface[0] -> w;
	BlockRect.h = BlockSurface[0] -> h;
	RandomSwap(arr);
	}


void Init() {
	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	srand((unsigned)time(NULL));
}

void FreeAndQuit() {
	SDL_FreeSurface(PlayUISurface);
	SDL_FreeSurface(StartBgSurface);
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	TTF_CloseFont(Font);
	SDL_Quit();
}
