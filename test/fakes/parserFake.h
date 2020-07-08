#ifndef __PARSER_FAKE_H__
#define __PARSER_FAKE_H__

#include "parser.h"

extern const ParserInterface ParserFake;

extern TerminalData_t parser_fake_json_return;
extern TerminalData_t parser_fake_terminal_input_terminal;
extern bool parser_fake_terminal_return;
extern TerminalData_t * parser_fake_terminal_list_input_terminals;
extern size_t parser_fake_terminal_list_input_count;
extern bool parser_fake_terminal_list_return;


#endif // __PARSER_FAKE_H__