#include "font.h"

#include <SDL_ttf.h>

TTF_Font * FONTS[FONT_COUNT];

void load_fonts() {
  char * file_names[FONT_COUNT];
  int font_size[FONT_COUNT];
  file_names[FONT_FREE_MONO_16] = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
  font_size[FONT_FREE_MONO_16] = 16;
  for (int i = 0; i < FONT_COUNT; i++) {
    if (!(FONTS[FONT_FREE_MONO_16] = TTF_OpenFont(file_names[i], font_size[i]))) {
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
		      "Could not open font: %s", file_names[i]);
    }
  }
}
