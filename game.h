#ifndef HUANG_TAO_666
#define HUANG_TAO_666

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void Init();
void Load();
void Play();
void FreeAndQuit();

static SDL_Event MainEvent;
static SDL_Event PlayEvent;
static SDL_Surface *StartBgSurface = NULL;
static SDL_Surface *PlayBgSurface = NULL;
static SDL_Surface *BlockSurface[16] = {NULL};
static SDL_Window *Window = NULL;
static SDL_Renderer *Renderer = NULL;
static TTF_Font *Font = NULL;
static SDL_Color FontColor = {255, 255, 255, 255};

#endif
