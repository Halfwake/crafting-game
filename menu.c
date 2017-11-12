#include "menu.h"

#include <SDL2/SDL.h>

#include <stdlib.h>

#include "state.h"

void menu_render(SDL_Renderer * renderer, union local_data local) {
  
}

enum callback_response menu_update(int delta, union local_data * local) {
  return CALLBACK_RESPONSE_CONTINUE;
}

enum callback_response menu_event(SDL_Event event, union local_data * local) {
  if (event.type == SDL_QUIT) {
    return CALLBACK_RESPONSE_QUIT;
  } else {
    return CALLBACK_RESPONSE_CONTINUE;
  }
}
