#include "font.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

TTF_Font * FONTS[FONT_COUNT];

void load_fonts() {
  char * file_names[FONT_COUNT];
  int font_size[FONT_COUNT];
  file_names[FONT_FREE_MONO_16] = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
  font_size[FONT_FREE_MONO_16] = 16;
  file_names[FONT_FREE_MONO_32] = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
  font_size[FONT_FREE_MONO_32] = 32;
  for (int i = 0; i < FONT_COUNT; i++) {
    if (!(FONTS[FONT_FREE_MONO_16] = TTF_OpenFont(file_names[i], font_size[i]))) {
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
		      "Could not open font: %s", file_names[i]);
    }
  }
}

SDL_Texture * render_text(char * text, TTF_Font * font, SDL_Color color, SDL_Renderer * renderer) {
  SDL_Surface * text_surface = TTF_RenderText_Solid(font, text, color);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, text_surface);
  SDL_FreeSurface(text_surface);
  return texture;
}
