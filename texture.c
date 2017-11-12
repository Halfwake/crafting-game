#include <SDL2/SDL.h>

#include <stdlib.h>

#include "texture.h"

SDL_Texture * TEXTURES[TEXTURE_COUNT];

void load_textures(SDL_Renderer * renderer) {
  char * file_names[TEXTURE_COUNT];
  file_names[BUTTON_HOVER] = "button_hover.bmp";
  file_names[BUTTON_NEUTRAL] = "button_neutral.bmp";

  for (int i = 0; i < TEXTURE_COUNT; i++) {
    SDL_Surface * surface = SDL_LoadBMP(file_names[i]);
    if (surface == NULL) {
      printf("Could not load texture [%s]: [%s]", file_names[i], SDL_GetError());
    }
    TEXTURES[i] = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (TEXTURES[i] == NULL) {
      printf("Could not load texture [%s]: [%s]", file_names[i], SDL_GetError());
    }
  }
}
