#include <SDL2/SDL.h>

#include "menu.h"
#include "callback.h"
#include "state.h"

int main() {
  // Initialize SDL and a rendering context.
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
  SDL_Window * window = SDL_CreateWindow("Graphics Test",
					 SDL_WINDOWPOS_CENTERED,
					 SDL_WINDOWPOS_CENTERED,
					 400,
					 400,
					 0);
  if (window == NULL) {
    printf("Could not open window: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Renderer * renderer =  SDL_CreateRenderer(window,
						-1,
						SDL_RENDERER_SOFTWARE);
  if (renderer == NULL) {
    printf("Could not create renderer: %s\n", SDL_GetError());
  }


  // Display Splash Screen
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
  SDL_Event event;

  // Store all render callbacks into a state enum indexed array.
  render_callback render_callbacks[GAME_STATE_COUNT];
  render_callbacks[GAME_STATE_MENU] = menu_render;

  // Store all update callbacks into a state enum indexed array.
  update_callback update_callbacks[GAME_STATE_COUNT];
  update_callbacks[GAME_STATE_MENU] = menu_update;
  
  // Store all event callbacks into a state enum indexed array.
  event_callback event_callbacks[GAME_STATE_COUNT];
  event_callbacks[GAME_STATE_MENU] = menu_event;

  // Create the game state visible on startup.
  struct game_state_local_data * local_state = malloc(sizeof(struct game_state_local_data));
  local_state->type  = GAME_STATE_MENU;
  local_state->tail = NULL;

  // The main game loop.
  while (local_state != NULL) {
    SDL_RenderClear(renderer);
    render_callbacks[local_state->type](renderer, local_state->local);
    SDL_RenderPresent(renderer);
    enum callback_response update_response = update_callbacks[local_state->type](0, &local_state->local);
    enum callback_response event_response = (SDL_PollEvent(&event)) ?
      event_callbacks[local_state->type](event, &local_state->local)
      : CALLBACK_RESPONSE_CONTINUE;
    if ((update_response == CALLBACK_RESPONSE_QUIT) || (event_response == CALLBACK_RESPONSE_QUIT)) {
      exit(0);
    } else if ((update_response == CALLBACK_RESPONSE_DONE) || (event_response == CALLBACK_RESPONSE_DONE)) {
      local_state = pop_state(local_state);
    }
  }    
  
  // Clean Up Resources.
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
