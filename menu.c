#include "menu.h"

#include <SDL2/SDL.h>

#include <stdlib.h>

#include "state.h"
#include "button.h"
#include "texture.h"
#include "dialog.h"

void menu_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local) {
  button_render(renderer, local->menu.quit_button);
  button_render(renderer, local->menu.new_game_button);
}

enum callback_response menu_update(int delta, union local_data * local, struct game_state_local_data * new_state) {
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT || button_is_clicked(local->menu.quit_button, event)) {
      char * choices[] = { "Yes", "No" };
      new_state->local = dialog_init(choices, 2);
      new_state->type = GAME_STATE_DIALOG;
      return CALLBACK_RESPONSE_CREATE;
    } else {
      return CALLBACK_RESPONSE_CONTINUE;
    }
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}

union local_data * menu_init() {
  union local_data * local = malloc(sizeof(union local_data));
  struct button * button = malloc(sizeof(struct button));
  button->hover = TEXTURES[BUTTON_HOVER];
  button->neutral = TEXTURES[BUTTON_NEUTRAL];
  SDL_Rect * rect = malloc(sizeof(SDL_Rect));
  rect->w = 256;
  rect->h = 64;
  rect->x = 400 - (rect->w / 2);
  rect->y = 400 - (rect->h / 2);
  button->rect = rect;
  local->menu.quit_button = button;

  button = malloc(sizeof(struct button));
  button->hover = TEXTURES[BUTTON_HOVER];
  button->neutral = TEXTURES[BUTTON_NEUTRAL];
  rect = malloc(sizeof(SDL_Rect));
  rect->w = 256;
  rect->h = 64;
  rect->x = 400 - (rect->w / 2);
  rect->y = 300 - (rect->h / 2);
  button->rect = rect;
  local->menu.new_game_button = button;

  return local;
}

void menu_destroy(union local_data  * state) {
  
}
