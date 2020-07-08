#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

static bool add_string(char * buff, size_t length, char * str);
static bool add_start(char * buff, size_t length);
static bool add_comma(char * buff, size_t length);
static bool add_id(int id, char * buff, size_t length);
static bool add_card_type(CardType_t card, char * buff, size_t length);
static bool append_card(char * buff, size_t length, bool add_comma, char * name);


bool parse_terminal(TerminalData_t terminal, char * buff, size_t length) {
  if (add_start(buff, length) == false) {
    return false;
  }
  if (add_id(terminal.id, buff, length) == false) {
    return false;
  }
  if (add_comma(buff, length) == false) {
    return false;
  }
  if (add_card_type(terminal.card_type, buff, length) == false) {
    return false;
  }

  return add_string(buff, length, ",\"TransactionType\":[\"Cheque\",\"Savings\"]}");
}

// Helper functions

static bool add_start(char * buff, size_t length) {
  return add_string(buff, length, "{");
}

static bool add_comma(char * buff, size_t length) {
  return add_string(buff, length, ",");
}

static bool add_end(char * buff, size_t length) {
  return add_string(buff, length, "}");
}

static bool add_id(int id, char * buff, size_t length) {
  char id_str[24] = { '\0' };
  (void) sprintf(id_str, "\"id\":%d", id);
  return add_string(buff, length, id_str);
}

static bool add_card_type(CardType_t card, char * buff, size_t length) {
  char card_str[64] = { '\0' };
  bool include_comma = false;

  if (add_string(card_str, 64, "\"cardType\":[") == false) {
    return false;
  }

  if (card & k_card_visa) {
    if (append_card(card_str, 64, include_comma, "\"Visa\"") == false) {
      return false;
    }
    include_comma = true;
  }

  if (card & k_card_master_card) {
    if (append_card(card_str, 64, include_comma, "\"MasterCard\"") == false) {
      return false;
    }
    include_comma = true;
  }

  if (card & k_card_eftpos) {
    if (append_card(card_str, 64, include_comma, "\"EFTPOS\"") == false) {
      return false;
    }
    include_comma = true;
  }

  if (add_string(card_str, 64, "]") == false) {
    return false;
  }

  return add_string(buff, length, card_str);
}

static bool append_card(char * buff, size_t length, bool include_comma, char * name) {
  if (include_comma) {
    if (add_comma(buff, length) == false) {
      return false;
    }
  }
  if (add_string(buff, length, name) == false) {
    return false;
  }
  return true;
}

static bool add_string(char * buff, size_t length, char * str) {
  if (strlen(buff) + strlen(str) >= length) {
    return false;
  }

  strcat(buff, str);
  return true;
}
