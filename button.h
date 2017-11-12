#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdbool.h>

#include <SDL2/SDL.h>

struct button {
  SDL_Rect * rect;
  SDL_Texture * hover;
  SDL_Texture * neutral;
};

void button_render(SDL_Renderer * renderer, struct button * button);
bool button_is_clicked(struct button button, SDL_Event event);

#endif
