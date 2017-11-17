#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "menu.h"
#include "callback.h"
#include "state.h"
#include "texture.h"
#include "dialog.h"
#include "font.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char * argv[]) {
  // Initialize SDL and related libraries.
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
		    "Could not init SDL: %s", SDL_GetError());
    return 1;
  }
  if (TTF_Init() < 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
		    "Could not init TTF: %s", TTF_GetError());
    return 1;
  }

  // Create a rendering context.
  SDL_Window * window = SDL_CreateWindow("Graphics Test",
					 SDL_WINDOWPOS_CENTERED,
					 SDL_WINDOWPOS_CENTERED,
					 SCREEN_WIDTH,
					 SCREEN_HEIGHT,
					 0);
  if (window == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO,
		    "Could not open window: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Renderer * renderer =  SDL_CreateRenderer(window,
						-1,
						SDL_RENDERER_TARGETTEXTURE);
  if (renderer == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO,
		    "Could not create renderer: %s\n", SDL_GetError());
  }


  // Display Splash Screen
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  load_textures(renderer);
  load_fonts();

  // Store all the destroy callbacks into a state enum indexed array.
  destroy_callback destroy_callbacks[GAME_STATE_COUNT];
  destroy_callbacks[GAME_STATE_MENU] = menu_destroy;
  destroy_callbacks[GAME_STATE_DIALOG] = dialog_destroy;
  
  // Store all render callbacks into a state enum indexed array.
  render_callback render_callbacks[GAME_STATE_COUNT];
  render_callbacks[GAME_STATE_MENU] = menu_render;
  render_callbacks[GAME_STATE_DIALOG] = dialog_render;

  // Store all update callbacks into a state enum indexed array.
  update_callback update_callbacks[GAME_STATE_COUNT];
  update_callbacks[GAME_STATE_MENU] = menu_update;
  update_callbacks[GAME_STATE_DIALOG] = dialog_update;
  
  // Create the game state visible on startup.
  struct game_state_local_data * local_state = malloc(sizeof(struct game_state_local_data));
  local_state->type  = GAME_STATE_MENU;
  local_state->tail = NULL;
  local_state->local = menu_init(renderer);

  struct game_state_local_data * old_local_state; // When we pop a state, we need a pointer to it so we can free it.
  struct game_state_local_data * new_state = malloc(sizeof(struct game_state_local_data));
  SDL_Texture * previous_texture = SDL_CreateTexture(renderer,
						     SDL_PIXELFORMAT_UNKNOWN,
						     SDL_TEXTUREACCESS_TARGET,
						     SCREEN_WIDTH,
						     SCREEN_HEIGHT);
  // The main game loop.
  while (local_state != NULL) {
    SDL_RenderClear(renderer);
    render_callbacks[local_state->type](renderer, local_state->previous_texture, local_state->local);
    SDL_RenderPresent(renderer);
    
    switch(update_callbacks[local_state->type](renderer, 0, local_state->local, new_state)) {
    case CALLBACK_RESPONSE_CONTINUE:
      break;
    case CALLBACK_RESPONSE_QUIT:
      exit(0);
    case CALLBACK_RESPONSE_DONE:
      old_local_state = local_state;
      local_state = pop_state(local_state);
      SDL_DestroyTexture(old_local_state->previous_texture);
      destroy_callbacks[local_state->type](old_local_state->local);
      continue;
    case CALLBACK_RESPONSE_CREATE:
      // Get a copy of the screen as a texture.
      SDL_SetRenderTarget(renderer, previous_texture);
      SDL_RenderClear(renderer);
      render_callbacks[local_state->type](renderer, local_state->previous_texture, local_state->local);
      new_state->previous_texture = previous_texture;
      SDL_SetRenderTarget(renderer, NULL);
      previous_texture = SDL_CreateTexture(renderer,
					   SDL_PIXELFORMAT_UNKNOWN,
					   SDL_TEXTUREACCESS_TARGET,
					   SCREEN_WIDTH,
					   SCREEN_HEIGHT);
      
      // Push the new state onto the state stack.
      local_state = push_state(local_state, new_state);
      new_state = malloc(sizeof(struct game_state_local_data));
      continue;
    }
  }
  
  // Clean Up Resources.
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_Quit();
  SDL_Quit();
  return 0;
}
