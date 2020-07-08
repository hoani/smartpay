#ifndef __HOANI_PARSER_H__
#define __HOANI_PARSER_H__

#include "terminal.h"
#include <stdint.h>
#include <stdbool.h>

bool parse_terminal(TerminalData_t terminal, char * buff, size_t length);

#endif //__HOANI_PARSER_H__