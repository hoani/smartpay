//
// Terminal storage - a standin for an actual database
//
// TODO:
// - Add a store_update(index, terminal) method
// - Add a store_delete(index) method
// - Make storage a dynamic list (so no longer limited to 0 - 99)

#include "store.h"

typedef struct {
  bool assigned;
  TerminalData_t terminal;
} StoredTerminal_t;

// TODO: It would be nice to make this a dynamically allocated list using
//       linked lists or something similar, this will have to do for demonstration.
static const int max_terminals = 100;
static StoredTerminal_t storage[100];
static int next_index = 0;

void store_init(void) {
  for (int i = 0; i< max_terminals; i++) {
    storage[i].assigned = false;
  }
  next_index = 0;
}

bool store_get(int index, TerminalData_t * terminal) {
  if (index >= next_index || index < 0) {
    return false;
  }
  if (storage[index].assigned == false) {
    return false;
  }
  *terminal = storage[index].terminal;
  return true;
}

int store_count(void) {
  return next_index;
}

int store_add(TerminalData_t terminal) {
  int item_index = next_index;
  storage[item_index].assigned = true;
  storage[item_index].terminal = terminal;
  // TODO: kind of wierd to store this twice, should reconsider this
  storage[item_index].terminal.id = item_index;
  next_index++;
  return item_index;
}