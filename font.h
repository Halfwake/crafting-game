#ifndef _FONT_H
#define _FONT_H

#include <SDL2/SDL_ttf.h>

enum font_id {
  FONT_FREE_MONO_16,
  FONT_COUNT
};

extern TTF_Font * FONTS[FONT_COUNT];

void load_fonts();

#endif
