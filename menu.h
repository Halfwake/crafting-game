#ifndef _MENU_H
#define _MENU_H

#include <SDL2/SDL.h>

#include "callback.h"
#include "state.h"

void menu_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local);
enum callback_response menu_update(int delta, union local_data * local, struct game_state_local_data * new_state);
union local_data * menu_init();
void menu_destroy(union local_data * local);

#endif
