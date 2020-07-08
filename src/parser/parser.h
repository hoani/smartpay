#ifndef __HOANI_PARSER_H__
#define __HOANI_PARSER_H__

#include "terminal.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  TerminalData_t (*json)(const char * buff);
  bool (*terminal)(TerminalData_t terminal, char * buff, size_t length);
  bool (*terminal_list)(TerminalData_t * terminals, size_t count, char * buff, size_t length);
} ParserInterface;

extern const ParserInterface Parser;


#endif //__HOANI_PARSER_H__