#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL2/SDL.h>

enum texture_id {
  BUTTON_HOVER,
  BUTTON_NEUTRAL,
  TEXTURE_COUNT
};

extern SDL_Texture * TEXTURES[TEXTURE_COUNT];

void load_textures(SDL_Renderer * renderer);

#endif
