#include "menu.h"

#include <SDL2/SDL.h>

#include <stdlib.h>

#include "state.h"
#include "button.h"
#include "texture.h"

void menu_render(SDL_Renderer * renderer, union local_data local) {
  button_render(renderer, local.menu.quit_button);
}

enum callback_response menu_update(int delta, union local_data * local, struct game_state_local_data * new_state) {
  return CALLBACK_RESPONSE_CONTINUE;
}

enum callback_response menu_event(SDL_Event event, union local_data * local, struct game_state_local_data * new_state) {
  if (event.type == SDL_QUIT) {
    return CALLBACK_RESPONSE_QUIT;
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}

void menu_init(struct game_state_local_data * new_state) {
  struct button * button = malloc(sizeof(struct button));
  button->hover = TEXTURES[BUTTON_HOVER];
  button->neutral = TEXTURES[BUTTON_NEUTRAL];
  SDL_Rect * rect;
  if ((rect = malloc(sizeof(SDL_Rect))) == NULL) {
    exit(1);
  }
  rect->x = 0;
  rect->y = 0;
  rect->w = 30;
  rect->h = 30;
  button->rect = rect;
  new_state->local.menu.quit_button = button;
}

void menu_destroy(struct game_state_local_data * state) {
  
}
