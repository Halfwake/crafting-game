#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <SDL2/SDL.h>

#include "state.h"

/*
 * The return value for callbacks. The return values allow the state to signal transfer from one state to another.
 * Note that the update and event callbacks can return different values in the same run of the main loop. The rules
 * for how this is handled are below.
 * A CALLBACK_RESPONSE_QUIT will override everything.
 * A CALLBACK_RESPONSE_DONE will override a CALLBACK_RESPONSE_CONTINUE or A CALLBACK_RESPONSE_CREATE.
 * A CALLBACK_RESPONSE_CREATE will override a CALLBACK_RESPONSE_CONTINUE.
 *
 * If a callback returns CALLBACK_RESPONSE_QUIT the game will quit after the current game tick is done executing.
 * If a callback returns CALLBACK_RESPONSE_CONTINUE nothing will happen.
 * If a callback returns CALLBACK_RESPONSE_DONE the game will pop the current state.
 * If a callback returns CREATE then the game will push a new state to the top of the state stack. Callbacks that
 * can return a response will include an argument for modifying whatever state will need to be updated.
 */
enum callback_response {
  CALLBACK_RESPONSE_QUIT,
  CALLBACK_RESPONSE_CONTINUE,
  CALLBACK_RESPONSE_DONE,
  CALLBACK_RESPONSE_CREATE
};

typedef void (*render_callback)(SDL_Renderer * renderer,
				SDL_Texture * previous_texture,
				union local_data * local);
typedef enum callback_response (*update_callback)(SDL_Renderer * renderer,
						  int delta,
						  union local_data * local,
						  struct game_state_local_data * new_state);
typedef void (*init_callback)(SDL_Renderer * renderer);			      
typedef void (*destroy_callback)(union local_data * local);

#endif
