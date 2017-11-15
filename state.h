#ifndef _STATE_H
#define _STATE_H

#include "button.h"
#include "SDL2/SDL.h"

enum game_state {
  GAME_STATE_MENU,
  GAME_STATE_DIALOG,
  GAME_STATE_COUNT
};

struct menu_local_data {
  struct button * quit_button;
  struct button * new_game_button;
};

struct dialog_local_data {
  char ** choices;
  size_t choice_count;
  struct button ** buttons;
};

union local_data {
  struct menu_local_data menu;
  struct dialog_local_data dialog;
};

struct game_state_local_data {
  enum game_state type;
  struct game_state_local_data * tail;
  SDL_Texture * previous_texture;
  union local_data * local;
};

struct game_state_local_data * pop_state(struct game_state_local_data * state);
struct game_state_local_data * push_state(struct game_state_local_data * head, struct game_state_local_data * new);

#endif
