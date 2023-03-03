#include "game.h"

void PrintBest() {
	FILE *fp = fopen("best.dat","r");
	assert(fp != NULL);
	char c = fgetc(fp);
	assert(fseek(fp, 0, SEEK_SET) != 1);
	if (c == EOF) {
		sprintf(BestChar, "--:--:--");
	}
	else {
		assert(fgets(BestChar, 10, fp) != NULL);
	}
	SDL_Surface *BestSurface = TTF_RenderUTF8_Blended(Font, BestChar, FontColor);
	SDL_Texture *BestTexture = SDL_CreateTextureFromSurface(Renderer, BestSurface);
	SDL_Rect BestRect = {210, 280, BestSurface -> w, BestSurface -> h};
	SDL_RenderCopy(Renderer, BestTexture, NULL, &BestRect);
	SDL_FreeSurface(BestSurface);
	SDL_DestroyTexture(BestTexture);
	fclose(fp);
}

void Printmsg() {
	if (msg) {
		SDL_Texture *msgTexture = SDL_CreateTextureFromSurface(Renderer, msgSurface);	
		SDL_Rect msgRect = {39, 340, msgSurface -> w, msgSurface ->h };
		SDL_RenderCopy(Renderer, msgTexture, NULL, &msgRect);
		SDL_DestroyTexture(msgTexture);
	}
}

void Swap() {
		int diff = abs(whichtwo[2] + whichtwo[3] - whichtwo[0] - whichtwo[1]);
		if(diff == 1) { 
			if (!arr[(whichtwo[2])][(whichtwo[3])]) {
				int temp;
				temp = arr[(whichtwo[0])][(whichtwo[1])];
				arr[(whichtwo[0])][(whichtwo[1])] = arr[(whichtwo[2])][(whichtwo[3])];
				arr[(whichtwo[2])][(whichtwo[3])] = temp;
			}
		}
}

void which() {		//Judge which two blocks will be swaped
	whichtwo[0] = (DownButtonY - 343) / 205;
	whichtwo[1] = (DownButtonX - 43) / 205;
	whichtwo[2] = (UpButtonY - 343) / 205;
	whichtwo[3] = (UpButtonX - 43) / 205;
}

int IfWin() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (count == arr[i][j])
				count++;
		}
	}
	if (count == 16)
		return 1;
	else
		return 0;
}

void PrintAll() {	//Print all Elements.
		SDL_Texture *PlayUITexture = SDL_CreateTextureFromSurface(Renderer, PlayUISurface);
		SDL_RenderCopy(Renderer, PlayUITexture, NULL, NULL);
		SDL_DestroyTexture(PlayUITexture);
		PrintTime();
		PrintBest();
		PrintBlocks();
		Printmsg();
		SDL_RenderPresent(Renderer);
}

void PrintTime() {
	if (!IfWin()) {	//If win, EndTime will not be updated.
		EndTime = time(NULL);
		DuraTime = (int) difftime(EndTime, StartTime);
	}
	else {
		time_t WinTime = EndTime;
		DuraTime = (int) difftime(WinTime, StartTime);
		FILE *fp = fopen("best.dat", "r");	
		assert(fp != NULL);
		char c = fgetc(fp);
		assert(fseek(fp, 0, SEEK_SET) != 1);
		if (c != EOF) {
			int hours, minutes, seconds, total_seconds;
			assert(sscanf(BestChar, "%d:%d:%d", &hours, &minutes, &seconds) == 3);
			total_seconds = hours * 3600 + minutes * 60 + seconds;
			if (DuraTime < total_seconds) {
				sprintf(BestChar, "%02d:%02d:%02d", DuraTime / 3600, (DuraTime / 60) % 60, DuraTime % 60);
				fclose(fp);
				FILE *fp = fopen("best.dat", "w");	
				assert(fputs(BestChar, fp) != EOF);
				fclose(fp);
			}
		}
		else {
			FILE *fp = fopen("best.dat", "w");
			sprintf(BestChar, "%02d:%02d:%02d", DuraTime / 3600, (DuraTime / 60) % 60, DuraTime % 60);
			assert(fputs(BestChar, fp) != EOF);
			fclose(fp);
		}
	}
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
			BlockRect.x = 43 + 205 * j;
			BlockRect.y = 343 + 205 * i;
			SDL_Texture *BlockTexture = NULL;
			BlockTexture = SDL_CreateTextureFromSurface(Renderer, BlockSurface[index]);
			SDL_RenderCopy(Renderer, BlockTexture, NULL, &BlockRect);
			SDL_DestroyTexture(BlockTexture);

		}
	}
}

void  RandomSwap() {	//Could only swaped with neighbor,otherwise there'll be no solution
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
	if (IfWin()) 
		EndTime = time(NULL);
	while (1) {
		if (!IfWin()) {
			PrintAll();
			while (SDL_PollEvent(&PlayEvent)) {
				switch (PlayEvent.type) {
					case SDL_QUIT:
						FreeAndQuit();
						break;
					case SDL_MOUSEBUTTONUP:
						UpButtonX = PlayEvent.button.x;
						UpButtonY = PlayEvent.button.y;
						printf("(%d,%d) in Play UI\n", PlayEvent.button.x, PlayEvent.button.y);
						int dx = abs(UpButtonX - DownButtonX);
						int dy = abs(UpButtonY - DownButtonY);
						if ((dy > 0 && dy < 200) || (dx > 0 && dx < 200) ) {
							which();
							printf("Move from (%d,%d) to (%d,%d)\n",whichtwo[0], whichtwo[1], whichtwo[2], whichtwo[3]);
							Swap();
						}
					case SDL_MOUSEBUTTONDOWN:
						DownButtonX = PlayEvent.button.x;
						DownButtonY = PlayEvent.button.y;
						break;
					default:
						break;
				}
			}
		}
			else {
				msg = 1;
				PrintAll();
				while (SDL_PollEvent(&PlayEvent)) {
					switch (PlayEvent.type) {
						case SDL_QUIT:
							FreeAndQuit();
							break;
						default:
							break;
					}
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
				break;
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
	msgSurface = IMG_Load("image/youwin.png");
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
	SDL_FreeSurface(msgSurface);
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	TTF_CloseFont(Font);
	SDL_Quit();
}
