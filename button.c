#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "button.h"
#include "font.h"

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
  SDL_Rect text_rect;
  text_rect.x = button->rect->x + button->rect->w / 4;
  text_rect.y = button->rect->y + button->rect->h / 4;
  text_rect.w = button->rect->w / 2;
  text_rect.h = button->rect->h / 2;
  SDL_RenderCopy(renderer, button->text, NULL, &text_rect);
}

bool button_is_clicked(struct button * button, SDL_Event event) {
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    SDL_Point mouse_point = {event.button.x, event.button.y};
    return SDL_PointInRect(&mouse_point, button->rect);
  } else {
    return false;
  }
}

struct button * button_init(SDL_Renderer * renderer, SDL_Rect * rect, SDL_Texture * hover, SDL_Texture * neutral, char * text) {
  struct button * button =  malloc(sizeof(struct button));
  button->rect = rect;
  button->hover = hover;
  button->neutral = neutral;
  SDL_Color color;
  color.r = 128;
  color.g = 128;
  color.b = 128;
  color.a = 128;
  SDL_Surface * surface = TTF_RenderText_Solid(FONTS[FONT_FREE_MONO_16], text, color);
  button->text = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return button;
}
