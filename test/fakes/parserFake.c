#include "parserFake.h"

static TerminalData_t parse_json(const char * buff);
static bool parse_terminal(TerminalData_t terminal, char * buff, size_t length);
static bool parse_terminal_list(TerminalData_t * terminals, size_t count, char * buff, size_t length);

TerminalData_t parser_fake_json_return;
TerminalData_t parser_fake_terminal_input_terminal;
bool parser_fake_terminal_return = false;
TerminalData_t * parser_fake_terminal_list_input_terminals = NULL;
size_t parser_fake_terminal_list_input_count = 0;
bool parser_fake_terminal_list_return = false;

const ParserInterface ParserFake = {
  parse_json,
  parse_terminal,
  parse_terminal_list
};

static TerminalData_t parse_json(const char * buff) {
  return parser_fake_json_return;
}

static bool parse_terminal(TerminalData_t terminal, char * buff, size_t length) {
  parser_fake_terminal_input_terminal = terminal;
  return parser_fake_terminal_return;
}

static bool parse_terminal_list(TerminalData_t * terminals, size_t count, char * buff, size_t length) {
  parser_fake_terminal_list_input_terminals = terminals;
  parser_fake_terminal_list_input_count = count;
  return parser_fake_terminal_list_return;
}