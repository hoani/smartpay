#ifndef __HOANI_STORE_H__
#define __HOANI_STORE_H__

#include "terminal.h"
#include <stdbool.h>
#include <stdint.h>

void store_init(void);
bool store_get(int index, TerminalData_t * terminal);
int store_count(void);

#endif //__HOANI_STORE_H__