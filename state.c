#include "state.h"

#include <stdlib.h>

struct game_state_local_data * pop_state(struct game_state_local_data * state) {
  struct game_state_local_data * new_top = state->tail;
  free(state);
  return new_top;
}

struct game_state_local_data * push_state(struct game_state_local_data * head, struct game_state_local_data * new) {
  new->tail = head;
  return head;
}
