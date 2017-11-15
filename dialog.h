#ifndef _DIALOG_H
#define _DIALOG_H

#include <SDL2/SDL.h>
#include "callback.h"
#include "state.h"

void dialog_render(SDL_Renderer * renderer, SDL_Texture * previous_texture, union local_data * local);
enum callback_response dialog_update(SDL_Renderer * renderer, int delta, union local_data * local, struct game_state_local_data * new_state);
union local_data * dialog_init(SDL_Renderer * renderer, char ** choices, size_t choice_count);
void dialog_destroy(union local_data * local);

#endif
