#include "popup.h"

#include <stdbool.h>

#include <SDL2/SDL.h>
#include "state.h"
#include "callback.h"
#include "texture.h"
#include "button.h"


void popup_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local) {
  SDL_SetTextureColorMod(previous_texture, 64, 64, 64);
  SDL_RenderCopy(renderer, previous_texture, NULL, NULL);
  for (int i = 0; i < local->popup.choice_count; i++) {
    button_render(renderer, local->popup.buttons[i]);
  }
}

enum callback_response popup_update(SDL_Renderer * renderer, int delta, union local_data * local, struct game_state_local_data * new_state) {
  SDL_Event event;
  if(SDL_PollEvent(&event)) {
    if (button_is_clicked(local->popup.buttons[0], event)) {
      return CALLBACK_RESPONSE_QUIT;
    } else if (button_is_clicked(local->popup.buttons[1], event)) {
      return CALLBACK_RESPONSE_DONE;
    } else {
      return CALLBACK_RESPONSE_CONTINUE;
    }
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}

union local_data * popup_init(SDL_Renderer * renderer, char ** choices, size_t choice_count) {
  union local_data * local = malloc(sizeof(union local_data));
  local->popup.choices = choices;
  local->popup.choice_count = choice_count;
  local->popup.buttons = malloc(sizeof(struct button *) * choice_count);
  for (int i = 0; i < choice_count; i++) {
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    rect->w = 256;
    rect->h = 64;
    rect->x = 400 - (rect->w / 2);
    rect->y = 300 - (rect->h / 2) + i * 128;
    local->popup.buttons[i] = button_init(renderer,
					  rect,
					  TEXTURES[BUTTON_HOVER],
					  TEXTURES[BUTTON_NEUTRAL],
					  choices[i]);
  }
  return local;
}

void popup_destroy(union local_data * local) {

}
