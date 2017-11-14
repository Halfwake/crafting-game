#include "dialog.h"

#include <stdbool.h>

#include <SDL2/SDL.h>
#include "state.h"
#include "callback.h"
#include "texture.h"
#include "button.h"


void dialog_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local) {
  SDL_SetTextureColorMod(previous_texture, 64, 64, 64);
  SDL_RenderCopy(renderer, previous_texture, NULL, NULL);
  for (int i = 0; i < local->dialog.choice_count; i++) {
    button_render(renderer, local->dialog.buttons + i);
  }
}

enum callback_response dialog_update(int delta, union local_data * local, struct game_state_local_data * new_state) {
  SDL_Event event;
  if(SDL_PollEvent(&event)) {
    if (button_is_clicked(local->dialog.buttons + 0, event)) {
      return CALLBACK_RESPONSE_DONE;
    } else if (button_is_clicked(local->dialog.buttons + 1, event)) {
      return CALLBACK_RESPONSE_QUIT;
    } else {
      return CALLBACK_RESPONSE_CONTINUE;
    }
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}

union local_data * dialog_init(char ** choices, size_t choice_count) {
  union local_data * local = malloc(sizeof(union local_data));
  local->dialog.choices = choices;
  local->dialog.choice_count = choice_count;
  local->dialog.buttons = malloc(sizeof(struct button) * choice_count);
  for (int i = 0; i < choice_count; i++) {
    SDL_Rect * rect = malloc(sizeof(SDL_Rect));
    rect->w = 256;
    rect->h = 64;
    rect->x = 400 - (rect->w / 2);
    rect->y = 400 - (rect->h / 2) + i * 128;
    local->dialog.buttons[i].rect = rect;
    local->dialog.buttons[i].hover = TEXTURES[BUTTON_HOVER];
    local->dialog.buttons[i].neutral = TEXTURES[BUTTON_NEUTRAL];
  }
  return local;
}

void dialog_destroy(union local_data * local) {

}
