#ifndef HUANG_TAO_666
#define HUANG_TAO_666
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void Swap();
void which();
void Init();
void Load();
void Play();
void PlayUI();
void FreeAndQuit();
void RandomSwap();
void PrintAll();
void PrintTime();
void PrintBlocks();

static int msg = 0;
static int DownButtonX, DownButtonY, UpButtonX, UpButtonY;
static char timechar[10];
static time_t StartTime, EndTime; 
static int whichtwo[4];
static int arr[4][4] = {
	{0,  1,  2,   3},
	{4,  5,  6,   7},
	{8,  9,  10, 11},
	{12, 13, 14, 15}
};


static SDL_Event MainEvent;
static SDL_Event PlayEvent;
static SDL_Surface *StartBgSurface = NULL;
static SDL_Surface *PlayUISurface = NULL;
static SDL_Surface *BlockSurface[16] = {NULL};
static SDL_Surface *msgSurface = NULL;
static SDL_Window *Window = NULL;
static SDL_Renderer *Renderer = NULL;
static TTF_Font *Font = NULL;
static SDL_Color FontColor = {255, 255, 255, 255};
static SDL_Rect BlockRect;

#endif
