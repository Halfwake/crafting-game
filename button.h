#ifndef _BUTTON_H
#define _BUTTON_H

#include <stdbool.h>

#include <SDL2/SDL.h>

struct button {
  SDL_Rect * rect;
  SDL_Texture * hover;
  SDL_Texture * neutral;
  SDL_Texture * text;
};

struct button *  button_init(SDL_Renderer * renderer, SDL_Rect * rect, SDL_Texture * hover, SDL_Texture * neutral, char * text);
void button_render(SDL_Renderer * renderer, struct button * button);
bool button_is_clicked(struct button * button, SDL_Event event);

#endif
