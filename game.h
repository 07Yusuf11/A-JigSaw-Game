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

static SDL_Window *Window = NULL;
static SDL_Renderer *Renderer = NULL;
static TTF_Font *Font = NULL;

#endif
