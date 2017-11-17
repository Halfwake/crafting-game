#include "menu.h"

#include <SDL2/SDL.h>

#include <stdlib.h>

#include "state.h"
#include "button.h"
#include "texture.h"
#include "popup.h"

void menu_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local) {
  button_render(renderer, local->menu.quit_button);
  button_render(renderer, local->menu.new_game_button);
}

enum callback_response menu_update(SDL_Renderer * renderer, int delta, union local_data * local, struct game_state_local_data * new_state) {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || button_is_clicked(local->menu.quit_button, event)) {
      char * choices[] = { "Yes", "No" };
      new_state->local = popup_init(renderer, choices, 2);
      new_state->type = GAME_STATE_POPUP;
      return CALLBACK_RESPONSE_CREATE;
    } else {
      return CALLBACK_RESPONSE_CONTINUE;
    }
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}

union local_data * menu_init(SDL_Renderer * renderer) {
  union local_data * local = malloc(sizeof(union local_data));
  SDL_Rect * rect = malloc(sizeof(SDL_Rect));
  rect->w = 256;
  rect->h = 64;
  rect->x = 400 - (rect->w / 2);
  rect->y = 400 - (rect->h / 2);
  local->menu.quit_button = button_init(renderer,
					rect,
					TEXTURES[BUTTON_HOVER],
					TEXTURES[BUTTON_NEUTRAL],
					"QUIT");
  rect = malloc(sizeof(SDL_Rect));
  rect->w = 256;
  rect->h = 64;
  rect->x = 400 - (rect->w / 2);
  rect->y = 300 - (rect->h / 2);
  local->menu.new_game_button = button_init(renderer,
					    rect,
					    TEXTURES[BUTTON_HOVER],
					    TEXTURES[BUTTON_NEUTRAL],
					    "NEW GAME");
  return local;
}

void menu_destroy(union local_data  * state) {
  
}
