#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#include "button.h"

void button_render(SDL_Renderer * renderer, struct button * button) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  SDL_Point mouse_point = {x, y};
  SDL_Texture * texture;
  if (SDL_PointInRect(&mouse_point, button->rect)) {
    texture = button->hover;
  } else {
    texture = button->neutral;
  }
  SDL_RenderCopy(renderer, texture, NULL, button->rect);
}

bool button_is_clicked(struct button button, SDL_Event event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse_point = {event.button.x, event.button.y};
    return SDL_PointInRect(&mouse_point, button.rect);
  } else {
    return false;
  }
}
