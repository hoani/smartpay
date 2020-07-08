
#include "store.h"

typedef struct {
  bool assigned;
  TerminalData_t terminal;
} StoredTerminal_t;

// TODO: It would be nice to make this a dynamically allocated list using
//       linked lists or something similar, this will have to do for demonstration.
static const int max_terminals = 100;
static StoredTerminal_t storage[100];

void store_init(void) {
  for (int i = 0; i< max_terminals; i++) {
    storage[i].assigned = false;
  }
}

bool store_get(int index, TerminalData_t * terminal) {
  return false;
}

int store_count(void) {
  return 0;
}