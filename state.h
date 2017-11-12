#ifndef _STATE_H
#define _STATE_H

enum game_state {
  GAME_STATE_MENU,
  GAME_STATE_COUNT
};

struct menu_local_data {
  int x_;
};

union local_data {
  struct menu_local_data menu;
};

struct game_state_local_data {
  enum game_state type;
  struct game_state_local_data * tail;
  union local_data local;
};

struct game_state_local_data * pop_state(struct game_state_local_data * state);
struct game_state_local_data * push_state(struct game_state_local_data * head, struct game_state_local_data * new);

#endif
